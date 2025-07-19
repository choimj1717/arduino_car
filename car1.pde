import processing.serial.*;

Serial myPort;
String incomingData = "";

float angle, distance;
ArrayList<PVector> points = new ArrayList<PVector>();
ArrayList<Integer> colors = new ArrayList<Integer>();

PFont font;
int lastMillis = 0;
int frameCounter = 0;
int fps = 0;

void setup() {
  size(700, 700);
  background(0);
  smooth();

  font = createFont("Arial", 14);
  textFont(font);

  // 시리얼 포트 설정 (Mac에서 포트 확인 필요)
  println(Serial.list());  // 포트 리스트 출력
  myPort = new Serial(this, Serial.list()[2], 9600);  // 적절한 인덱스로 수정
  myPort.bufferUntil('\n');
}

void draw() {
  background(0);
  translate(width/2, height/2);

  // 그리드 원
  stroke(50);
  noFill();
  for (int r = 50; r <= 250; r += 50) {
    ellipse(0, 0, r*2, r*2);
  }

  // 중심 십자선
  stroke(70);
  line(-width/2, 0, width/2, 0);
  line(0, -height/2, 0, height/2);

  // 스캔 라인 (현재 각도)
  stroke(255, 255, 0);
  float xLine = 260 * cos(angle);
  float yLine = 260 * sin(angle);
  line(0, 0, xLine, yLine);

  // 점 찍기
  noStroke();
  for (int i = 0; i < points.size(); i++) {
    fill(colors.get(i));
    PVector p = points.get(i);
    ellipse(p.x, p.y, 6, 6);
  }

  // 텍스트 UI
  fill(255);
  textAlign(LEFT);
  text("각도: " + int(degrees(angle)) + "°", -width/2 + 20, -height/2 + 30);
  text("거리: " + nf(distance, 1, 1) + " cm", -width/2 + 20, -height/2 + 50);
  text("FPS: " + fps, -width/2 + 20, -height/2 + 70);

  // FPS 계산
  frameCounter++;
  if (millis() - lastMillis >= 1000) {
    fps = frameCounter;
    frameCounter = 0;
    lastMillis = millis();
  }
}

void serialEvent(Serial myPort) {
  incomingData = trim(myPort.readStringUntil('\n'));
  if (incomingData == null || !incomingData.contains(",")) return;

  String[] data = split(incomingData, ",");
  if (data.length < 2) return;

  try {
    angle = radians(float(data[0]));
    distance = float(data[1]);
    float scaledDist = map(distance, 0, 100, 0, 250);  // 거리 → 화면 반지름
    float x = scaledDist * cos(angle);
    float y = scaledDist * sin(angle);
    points.add(new PVector(x, y));

    // 색상: 가까울수록 빨강, 멀수록 파랑
    int c = color(map(distance, 0, 100, 255, 0), map(distance, 0, 100, 0, 255), 128);
    colors.add(c);

    // 오래된 점 삭제
    if (points.size() > 100) {
      points.remove(0);
      colors.remove(0);
    }

  } catch(Exception e) {
    println("파싱 오류: " + incomingData);
  }
}
