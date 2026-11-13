# Morse Code Project

This project consists of several Arduino sketches designed to handle different aspects of Morse code communication. Below is a brief overview of each sketch and how they interact.

## Table of Contents
1. **button-to-morse-tester.ino**
2. **client1.ino** (FINAL CODE)
3. **client2.ino** (FINAL CODE)
4. **oled-bitmap-tester.ino**
5. **pubsub-wm-test.ino**


## Video STEP BY STEP
[[Morse Code Project STEP BY STEP]](https://www.instagram.com/reel/CxbDOlOxXBF/?exln=MXkwYTMxbXh6dHkwOA==)

## 1. button-to-morse-tester.ino
This sketch is responsible for converting button presses into Morse code characters and sending them over the serial port.

### Key Features:
- Converts button presses into dots and dashes.
- Sends a space between words.
- Uses a simple state machine to track button presses and releases.

### Code Snippet:
```cpp
void loop() {
  if (!bp && !digitalRead(3) && !br && space_en){
    space_end = millis();
    if ((space_s != 0) && ((space_end - space_s)>300)) Serial.print(" ");
    butt_pr = millis();
    bp = !bp;
    space_en = !space_en;
    delay(10);
  }
  if (bp && digitalRead(3) && !br){
    butt_rls = millis();
    br = !br;
    delay(10);
  }
  if (digitalRead(3) && br && bp && !space_en){
    if ((butt_rls - butt_pr)>5 && (butt_rls - butt_pr)<190) Serial.print(".");
    if ((butt_rls - butt_pr)>= 190) Serial.print("_");
    space_s = millis();
    br = !br;
    bp = !bp;
    space_en = !space_en;
  }
}
```

## 2. client1.ino
This sketch is designed to receive Morse code via a paddle and send it over MQTT.

### Key Features:
- Converts paddle movements into dots and dashes.
- Sends a message over MQTT.
- Handles WiFi settings via a button press.

### Code Snippet:
```cpp
void loop() {
  if (!bp && !digitalRead(PIN_PADDLE) && !br && space_en){
    space_end = millis();
    if ((space_s != 0) && ((space_end - space_s)>300)) message += String("/");
    butt_pr = millis();
    bp = !bp;
    space_en = !space_en;
    delay(10);
  }

  if(!digitalRead(PIN_PADDLE)) digitalWrite(OUT, HIGH); 
  else digitalWrite(OUT, LOW);

  if (bp && digitalRead(PIN_PADDLE) && !br){
    butt_rls = millis();
    br = !br;
    delay(10);
  }

  if (digitalRead(PIN_PADDLE) && br && bp && !space_en){
    if ((butt_rls - butt_pr)>5 && (butt_rls - butt_pr)<190) message += String(".");
    if ((butt_rls - butt_pr)>= 190) message += String("_");
    space_s = millis();
    br = !br;
    bp = !bp;
    space_en = !space_en;
  }
}
```

## 3. client2.ino
This sketch is designed to receive Morse code via a paddle and display it on an OLED screen.

### Key Features:
- Converts paddle movements into dots and dashes.
- Displays the received message on an OLED screen.

### Code Snippet:
```cpp
void loop() {
  if (!bp && !digitalRead(PIN_PADDLE) && !br && space_en){
    space_end = millis();
    if ((space_s != 0) && ((space_end - space_s)>300)) message += String("/");
    butt_pr = millis();
    bp = !bp;
    space_en = !space_en;
    delay(10);
  }

  if(!digitalRead(PIN_PADDLE)) digitalWrite(OUT, HIGH); 
  else digitalWrite(OUT, LOW);

  if (bp && digitalRead(PIN_PADDLE) && !br){
    butt_rls = millis();
    br = !br;
    delay(10);
  }

  if (digitalRead(PIN_PADDLE) && br && bp && !space_en){
    if ((butt_rls - butt_pr)>5 && (butt_rls - butt_pr)<190) message += String(".");
    if ((butt_rls - butt_pr)>= 190) message += String("_");
    space_s = millis();
    br = !br;
    bp = !bp;
    space_en = !space_en;
  }
}
```

## 4. oled-bitmap-tester.ino
This sketch is designed to test the OLED display with a bitmap.

### Key Features:
- Displays a bitmap on the OLED screen.

### Code Snippet:
```cpp
const uint8_t bitmap[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
```

## 5. pubsub-wm-test.ino
This sketch is designed to test MQTT communication.

### Key Features:
- Connects to an MQTT broker.
- Publishes a test message.
- Subscribes to a topic and prints received messages.

### Code Snippet:
```cpp
void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);
       retries--;
       if (retries == 0) {
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
```

## Installation and Usage
1. **Hardware Setup:**
   - Connect the buttons, paddles, and OLED display according to the project documentation.
   - Ensure the Arduino board is properly powered and connected to your computer.

2. **Software Setup:**
   - Open the Arduino IDE and load the sketches into the appropriate boards.
   - Configure the WiFi settings and MQTT broker details in the respective sketches.
   - Upload the sketches to the Arduino boards.

3. **Testing:**
   - Press the buttons and paddles to test Morse code functionality.
   - Observe the OLED display and serial output to verify correct operation.



## Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
