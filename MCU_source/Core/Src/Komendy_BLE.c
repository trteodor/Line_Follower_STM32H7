
void PRZYPISYWANIEWARTOSCI()
{

	//Z Ekranu "PODST"
  if(wynik==1){
	  Kp=atof(DANE_BLE);
	  EEPROM_WRITE_FLOAT(50,&Kp);

    }
  if(wynik==2){
    Kd=atof(DANE_BLE);
    EEPROM_WRITE_FLOAT(55,&Kd);
  }
  if(wynik==103){
    pr_pocz_silnikow=atof(DANE_BLE);
    EEPROM_WRITE_FLOAT(60,&pr_pocz_silnikow);
}
  if(wynik==4) {
    Ki=atof(DANE_BLE);
    EEPROM_WRITE_FLOAT(65,&Ki);
  }



  //Z Ekranu "CZUJNIKI"

  if(wynik==10) {
    er1=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(70,&er1);

  }
    if(wynik==11) {
    er2=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(75,&er2);

  }
    if(wynik==12) {
    er3=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(80,&er3);

  }
    if(wynik==13) {
    er4=atof(DANE_BLE);
    EEPROM_WRITE_FLOAT(85,&er4);

  }
    if(wynik==14) {
    er5=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(90,&er5);

  }
    if(wynik==15) {
    er6=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(100,&er6); //adres 95 uszkodzony? :/

  }
    if(wynik==16) {
    er7=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(105,&er7);

  }
    if(wynik==17) {
    	err_max=atof(DANE_BLE); EEPROM_WRITE_FLOAT(115,&err_max); //adres 110 uszkodzony? :/

  }




					if(wynik==40) {
						czcz1=atoi(DANE_BLE);  EEPROM_WRITE_INT(265,&czcz1); //adres 200 uszkodzony? tak
						}
					  if(wynik==41) {
						  czcz2=atoi(DANE_BLE);  EEPROM_WRITE_INT(245,&czcz2); //adres 205 uszkodzony? tak nwm o co kmn anyway
						  }
					  if(wynik==42) {
						  czcz3=atoi(DANE_BLE);  EEPROM_WRITE_INT(210,&czcz3);
						  }
					  if(wynik==43) {
						  czcz4=atoi(DANE_BLE);  EEPROM_WRITE_INT(215,&czcz4);
						  }
					  if(wynik==44) {
						  czcz5=atoi(DANE_BLE);  EEPROM_WRITE_INT(220,&czcz5);
						  }
						  if(wynik==45) {
							  czcz6=atoi(DANE_BLE);  EEPROM_WRITE_INT(225,&czcz6);
						  }
					  if(wynik==46) {
						  czcz7=atoi(DANE_BLE);  EEPROM_WRITE_INT(230,&czcz7);
					  }
						if(wynik==47) {
							czcz8=atoi(DANE_BLE);  EEPROM_WRITE_INT(235,&czcz8);
						}




        //@@@@@@@@@@@@@@@
//Z Ekranu "ZAAW"

				if(wynik==30) {
					MAX_PID=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(400,&MAX_PID);

			  }
				  if(wynik==131) {
				pr_tyl=atoi(DANE_BLE);  EEPROM_WRITE_INT(405,&pr_tyl);

			  }
				  if(wynik==32) {
					  SUMA_MAX=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(410,&SUMA_MAX);

			  }
				  if(wynik==33) {
				CzasProbkowania_CZ_Rozniczkujacego=atoi(DANE_BLE);

			   EEPROM_WRITE_INT(420,&CzasProbkowania_CZ_Rozniczkujacego);

			  }

				  if(wynik==134) { //test silnika wl
					  T_SIL=1;
			  }
				  if(wynik==135) { //tesy silnika wyl
					  T_SIL=0;
			  }

				  if(wynik==36) {
					  ZMIENNA3=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(440,&ZMIENNA3);

			   }

				  if(wynik==37) {
					  ZMIENNA4=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(445,&ZMIENNA4);
					  HAL_NVIC_SystemReset();
			  }

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ IR STATE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      if(wynik==38) {
    	  IR_READY=atoi(DANE_BLE);  EEPROM_WRITE_INT(450,&IR_READY);

  }
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ IR STATE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        if(wynik==39) {
        	LED_BLINK=atoi(DANE_BLE);;  EEPROM_WRITE_INT(455,&LED_BLINK);
      }
  //@@@@@@@@@@@@@@@@
}
