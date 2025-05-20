# reflection-arduino

本專案結合網頁互動彩繪玻璃背景（stained-glass.html）與 Arduino UNO + HC-SR04 超音波感測器，實現感測距離控制網頁視覺效果的應用。

## stained-glass.html 說明

此網頁會顯示動態的「彩繪玻璃」背景，並可根據滑鼠或 Arduino 感測距離互動。右上角有多種設定：

- **主題**  
  選擇不同色彩主題，影響每個玻璃區塊的色調。  
  - 彩虹：多彩色調
  - 暖色、冷色：偏紅/藍色系
  - 單色藍/綠/紅/黃/紫：單一色系

- **萬花筒**  
  勾選後，畫面呈現萬花筒對稱效果。

- **分割**  
  萬花筒分割數，數字越大對稱區塊越多。

- **X軸高亮**  
  勾選後，滑鼠或感測器控制的 X 軸位置會讓該垂直區域的玻璃變亮。

- **選擇連接埠**  
  點擊後可選擇 Arduino 連接埠，連接後可由 Arduino 控制互動（如以距離感測器取代滑鼠 X）。

### 感測互動

- 預設以滑鼠 X/Y 控制玻璃亮度。
- 若連接 Arduino，則以 HC-SR04 感測距離正規化為 0~1，對應畫面 X 軸，控制高亮區域。

## Arduino UNO + HC-SR04 接線

- **HC-SR04 VCC** → Arduino 5V
- **HC-SR04 GND** → Arduino GND
- **HC-SR04 TRIG** → Arduino D9
- **HC-SR04 ECHO** → Arduino D10

> 注意：ECHO 腳位輸出 5V，若接 ESP32/ESP8266 請加分壓保護。

## Arduino 程式

請參考 `distance_to_html.ino`，其功能如下：

- 讀取 HC-SR04 距離，正規化為 0~1。
- 透過序列埠每 50ms 輸出 `mouseX:0.53` 格式。
- 可用序列指令 `max:數值` 設定最大感測距離（單位：cm）。

## 使用方式

1. 將 `distance_to_html.ino` 上傳至 Arduino UNO。
2. 以 USB 連接電腦，開啟 stained-glass.html（需支援 Web Serial 的瀏覽器，如 Chrome）。
3. 點選「選擇連接埠」並選擇 Arduino。
4. 移動手於感測器前方，網頁會根據距離變化高亮區域。

---