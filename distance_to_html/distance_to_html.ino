// HC-SR04 pins
const int trigPin = 9;
const int echoPin = 10;

long duration;
float distance;
float minDistance = 5.0;   // 新增最小距離 (cm)
float maxDistance = 20.0;  // 預設最大距離 (cm)

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // 檢查序列埠是否有設定指令
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd.startsWith("max:")) {
      float val = cmd.substring(4).toFloat();
      if (val > 0) maxDistance = val;
    } else if (cmd.startsWith("min:")) {
      float val = cmd.substring(4).toFloat();
      if (val >= 0) minDistance = val;
    }
  }

  // 觸發 HC-SR04
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 讀取回波
  duration = pulseIn(echoPin, HIGH, 30000); // 最長 30ms (約5m)
  if (duration == 0) {
    // 無回波，視為最大距離
    distance = maxDistance;
  } else {
    distance = duration * 0.0343 / 2.0; // cm
  }

  // 正規化到 0~1，考慮 minDistance
  float norm = (distance - minDistance) / (maxDistance - minDistance);
  if (norm < 0) norm = 0;
  if (norm > 1) norm = 1;

  // 輸出到序列埠
  // Serial.print("distance: ");
  // Serial.print(distance);
  // Serial.print(" cm, norm: ");
  // Serial.println(norm, 3);

  // 傳送給 stained-glass.html
  Serial.print("mouseX:");
  Serial.println(norm, 3);

  delay(50); // 20Hz
}
