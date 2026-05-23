int do1 = 13, vang1 = 12, xanh1 = 11;
int do3 = 10, vang3 = 9, xanh3 = 8;
int do2 = 7, vang2 = 6, xanh2 = 5; 
int do4 = 4, vang4 = 3, xanh4 = 2;

#define LDR_PIN A0

unsigned long thoiGianTruoc = 0;
unsigned long thoiGianChopVang = 0;
unsigned long thoiGianCho = 4000;
bool trangThaiChopVang = false;

int trangThai = 0;

void setup() {
  Serial.begin(9600); 
  for (int i = 2; i <= 13; i++) pinMode(i, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  
  chuyenPhaDen(0);
}

void trucDoc(int tDo, int tVang, int tXanh) {
  digitalWrite(do1, tDo);   digitalWrite(do3, tDo);
  digitalWrite(vang1, tVang); digitalWrite(vang3, tVang);
  digitalWrite(xanh1, tXanh); digitalWrite(xanh3, tXanh);
}

void trucNgang(int tDo, int tVang, int tXanh) {
  digitalWrite(do2, tDo);   digitalWrite(do4, tDo);
  digitalWrite(vang2, tVang); digitalWrite(vang4, tVang);
  digitalWrite(xanh2, tXanh); digitalWrite(xanh4, tXanh);
}

void chuyenPhaDen(int phaMoi) {
  trangThai = phaMoi;
  if (phaMoi == 0) { 
    trucDoc(LOW, LOW, HIGH); trucNgang(HIGH, LOW, LOW); 
    thoiGianCho = 4000; // 4 giây
  }
  else if (phaMoi == 1) { 
    trucDoc(LOW, HIGH, LOW); trucNgang(HIGH, LOW, LOW); 
    thoiGianCho = 1000; // 1 giây
  }
  else if (phaMoi == 2) { 
    trucDoc(HIGH, LOW, LOW); trucNgang(LOW, LOW, HIGH); 
    thoiGianCho = 4000; // 4 giây
  }
  else if (phaMoi == 3) { 
    trucDoc(HIGH, LOW, LOW); trucNgang(LOW, HIGH, LOW); 
    thoiGianCho = 1000; // 1 giây
  }
}

void loop() {
  unsigned long hienTai = millis();
  int doSang = analogRead(LDR_PIN);
   Serial.print("Do sang: "); Serial.println(doSang); 
  if (doSang < 980) { 
    if (hienTai - thoiGianChopVang >= 500) { 
      thoiGianChopVang = hienTai;
      trangThaiChopVang = !trangThaiChopVang;
      trucDoc(LOW, trangThaiChopVang, LOW);
      trucNgang(LOW, trangThaiChopVang, LOW);
    }
    thoiGianTruoc = hienTai;   
    return;
  }

  if (hienTai - thoiGianTruoc >= thoiGianCho) {
    thoiGianTruoc = hienTai;
    
    int phaTiepTheo = trangThai + 1;
    if (phaTiepTheo > 3) {
      phaTiepTheo = 0;
    }
    
    chuyenPhaDen(phaTiepTheo);
  }
}