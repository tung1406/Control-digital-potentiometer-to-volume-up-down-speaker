#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);
//0x3f là địa chỉ màn hình trong bus I2C.       //I2C address 0x3f, 20 columns and 4 rows

int blr1 = 0;     //chân 0
int blr2 = 1;

int bsub1 = 2;     
int bsub2 = 3;

int potlr = A0, potsub = A1; // chan ket noi X9c013             //the connect pin of X9C103 

int Readlr, Readsub;

int lr , sub ;

int buttonStatelr1 = 0;
int buttonStatelr2 = 0;

int buttonStatesub1 = 0;
int buttonStatesub2 = 0;

#define CSl 4    // pin 2, chân cho phép kênh trái              //left channel chip select
#define UDl 6    // pin 3 chân chỉnh hướng lên/xuống kênh trái  //left channel up/down wiper
#define INCl 5   // pin 4 chân chạy cần gạt kênh trái           //left channel increment

#define CSr 7    // pin 2 chân cho phép kênh phải
#define UDr 9   // pin 3 chân chỉnh hướng lên/xuống kênh phải
#define INCr 8   // pin 4 chân chạy cần gạt kênh phải

#define CSsub 10    // pin 2 chân cho phép kênh sub
#define UDsub 12   // pin 3 chân chỉnh hướng lên/xuống kênh sub
#define INCsub 11   // pin 4 chân chạy cần gạt kênh sub

////////////////////////////////////////////////////////////////////////setup/////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);

  lcd.init();       //Khởi chạy màn hình.                       //initialize the lcd
  lcd.backlight();   //Bật đèn nền                              //open the backlight

  lcd.setCursor(7, 0);                                 
  lcd.print("DO AN 2");

  lcd.setCursor(0, 1); 
  lcd.print("Volume L/R:");
  lcd.setCursor(11, 1);
  lcd.print(lr);
//  lcd.setCursor(13, 1);
//  lcd.print("%");
  
  lcd.setCursor(4, 3);
  lcd.print("Volume Sub:");
  lcd.setCursor(15, 3);
  lcd.print(sub);
  // lcd.setCursor(14, 3);
  // lcd.print("%");

  pinMode(CSl, OUTPUT);
  pinMode(UDl, OUTPUT);
  pinMode(INCl, OUTPUT);

  pinMode(CSr, OUTPUT);
  pinMode(UDr, OUTPUT);
  pinMode(INCr, OUTPUT);

  pinMode(blr1, INPUT);
  pinMode(blr2, INPUT);

  pinMode(CSsub, OUTPUT);
  pinMode(UDsub, OUTPUT);
  pinMode(INCsub, OUTPUT);

  pinMode(bsub1, INPUT);
  pinMode(bsub2, INPUT);
}

////////////////////////////////////////////////////////////////////////upl/////////////////////////////////////////////////////////////////////////////////
void Upl() {
   digitalWrite(CSl,LOW); //cho phép biến trở hoạt động khi ngõ vào thấp    //enable potentiometer to operate when input is low
   digitalWrite(UDl,HIGH);//mức cao cho phép cần gạt di chuyển lên          //high level allows the wiper to move up
   digitalWrite(INCl,HIGH);
   delay(50);
   digitalWrite(INCl,LOW);//điều khiển cần gạt di chuyển                    //increase the wiper

    lcd.setCursor(11, 1);
    lcd.print(lr);
   
}
////////////////////////////////////////////////////////////////////////downl/////////////////////////////////////////////////////////////////////////////////
void Downl() {
   digitalWrite(CSl,LOW); //cho phép biến trở hoạt động khi ngõ vào thấp
   digitalWrite(UDl,LOW); //mức thấp cho phép cần gạt di chuyển xuống       //low level allows the wiper to move down
   digitalWrite(INCl,HIGH);
   delay(50);
   digitalWrite(INCl,LOW);//điều khiển cần gạt di chuyển

    lcd.setCursor(11, 1);
    lcd.print(lr);
}
////////////////////////////////////////////////////////////////////////upr/////////////////////////////////////////////////////////////////////////////////
void Upr() {
   digitalWrite(CSr,LOW);
   digitalWrite(UDr,HIGH);
   digitalWrite(INCr,HIGH);
   delay(50);
   digitalWrite(INCr,LOW);
}
////////////////////////////////////////////////////////////////////////downr/////////////////////////////////////////////////////////////////////////////////
void Downr() {
   digitalWrite(CSr,LOW);
   digitalWrite(UDr,LOW);
   digitalWrite(INCr,HIGH);
   delay(50);
   digitalWrite(INCr,LOW);
}
////////////////////////////////////////////////////////////////////////storelr/////////////////////////////////////////////////////////////////////////////////
void storelr(){
 digitalWrite(INCl,HIGH);//lưu giá trị biến trở khi INC và CS đồng thời mức cao       //store the rheostat value when INC and CS are simultaneously high
 digitalWrite(CSl,HIGH); //cho phép biến trở lưu giá trị khi ngõ vào cao              //allows potentiometer to store value when input is high
 delay(50);
 digitalWrite(CSl,LOW);
 }
////////////////////////////////////////////////////////////////////////readlr/////////////////////////////////////////////////////////////////////////////////
void readlr(){
  Readlr = analogRead(potlr); //đọc giá trị biến trở                                            //read the rheostat value
  lr= 102 - round(Readlr/10); //tính toán và chuyển đổi giá trị biến trở sang giá trị âm lượng    //calculate and convert rheostat value to volume value

  buttonStatelr1 = digitalRead(blr1);
  buttonStatelr2 = digitalRead(blr2);

  if (buttonStatelr1 == 0)  {Upl();} //Upr();}
  if (buttonStatelr2 == 0) {Downl();}// Downr();}
  if (buttonStatelr1 == 0 && buttonStatelr2 == 0) storelr();

  if (lr > 99) {
    lcd.setCursor(14, 1);
    lcd.print("%  ");
  }
   else if (lr < 10){
    lcd.setCursor(12, 1);
    lcd.print("%   ");
  }
  else {lcd.setCursor(13, 1);
  lcd.print("%   ");
  }

}
////////////////////////////////////////////////////////////////////////upsub/////////////////////////////////////////////////////////////////////////////////
void Upsub() {
   digitalWrite(CSsub,LOW);
   digitalWrite(UDsub,HIGH);
   digitalWrite(INCsub,HIGH);
   delay(50);
   digitalWrite(INCsub,LOW);

  lcd.setCursor(15, 3);
  lcd.print(sub);
   
}
////////////////////////////////////////////////////////////////////////downsub/////////////////////////////////////////////////////////////////////////////////
void Downsub() {
   digitalWrite(CSsub,LOW);
   digitalWrite(UDsub,LOW);
   digitalWrite(INCsub,HIGH);
   delay(50);
   digitalWrite(INCsub,LOW);

  lcd.setCursor(15, 3);
  lcd.print(sub);
}
////////////////////////////////////////////////////////////////////////storesub/////////////////////////////////////////////////////////////////////////////////
void storesub(){
 digitalWrite(INCsub,HIGH);
 digitalWrite(CSsub,HIGH);
 delay(50);
 digitalWrite(CSsub,LOW);
 }
////////////////////////////////////////////////////////////////////////readsub/////////////////////////////////////////////////////////////////////////////////
void readsub(){
  Readsub = analogRead(potsub);
  sub= 102 - round(Readsub/10);

  buttonStatesub1 = digitalRead(bsub1);
  buttonStatesub2 = digitalRead(bsub2);

  if (buttonStatesub1 == 0)  Upsub();
  if (buttonStatesub2 == 0) Downsub();
  if (buttonStatesub1 == 0 && buttonStatesub2 == 0) storesub();

  if (sub > 99) {
    lcd.setCursor(18, 3);
    lcd.print("% ");
  }
   else if (sub < 10){
    lcd.setCursor(16, 3);
    lcd.print("%   ");
  }
  else {lcd.setCursor(17, 3);
  lcd.print("%  ");
  }

}

////////////////////////////////////////////////////////////////////////loop/////////////////////////////////////////////////////////////////////////////////
void loop() {
  readlr();
 readsub();
  
  Serial.print("Analog reading left/right= ");
  Serial.println(Readlr);
  Serial.println(lr);
  Serial.println(buttonStatelr1);
  Serial.println(buttonStatelr2);
  delay(100);

  // Serial.print("Analog reading sub= ");
  // Serial.println(Readsub);
  // Serial.println(sub);
  // Serial.println(buttonStatesub1);
  // Serial.println(buttonStatesub2);
  // delay(100);
 
}
