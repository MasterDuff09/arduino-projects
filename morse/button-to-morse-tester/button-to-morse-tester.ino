long butt_pr = 0, butt_rls = 0, space_s = 0, space_end = 0;
int bp = 0, br = 0, space_en = 1;

void setup() {
  Serial.begin(115200);
  pinMode(3, INPUT_PULLUP);

}

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
