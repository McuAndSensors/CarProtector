/*
 * LCD_Interface.c
 *
 * Created: 20/11/2016 19:36:14
 *  Author: Azriel
 */ 
void Create_button(word Button_X_Size, word Button_Y_Size, word X_Location, word Y_Location,unsigned char Red,unsigned char Green,unsigned char Blue)
{
	unsigned char jump_color_brighter = 160/(Button_Y_Size/2);
	Red=Green=Blue=90;
	for(word i = 0; i <= (Button_Y_Size/2); i++)
	{
		
		myGLCD.setColor(Red, Green, Blue);
		
		//Up line
		myGLCD.drawLine(X_Location+i ,(Y_Location+i) ,(X_Location+Button_X_Size-i) ,(Y_Location+i));
		
		//Down line
		myGLCD.drawLine(X_Location+i ,(Y_Location+Button_Y_Size-i) ,(X_Location+Button_X_Size-i) ,(Y_Location+Button_Y_Size-i));
		
		//Left line
		myGLCD.drawVLine(X_Location+i ,(Y_Location+i) ,(Button_Y_Size-i-i));
		
		//Right line
		myGLCD.drawVLine(X_Location+Button_X_Size-i ,(Y_Location+i) ,(Button_Y_Size-i-i));
		
		Red = Blue = Green += jump_color_brighter;
	}
}

void Seven_Segment_4_5(unsigned char Size_1_To_5, word X_Location, word Y_Location, char Display_Num)
{
	unsigned char X_Size, Y_Size;
	if (Size_1_To_5 <= 0 || Size_1_To_5 > 5)
	{
		Size_1_To_5 = 0x01;
	}
	switch(Size_1_To_5)
	{
		case 1:X_Size = 10, Y_Size = 2; break;
		case 2:X_Size = 20, Y_Size = 4; break;
		case 3:X_Size = 28, Y_Size = 9; break;
		case 4:X_Size = 48, Y_Size = 13; break;
		case 5:X_Size = 70, Y_Size = 17; break;
	}
	for(word i = 0; i <= (Y_Size/2); i++)
	{
		myGLCD.setColor(255, 0, 0);
		
		if (Display_Num == 0 || Display_Num >= 5 || Display_Num == 2 || Display_Num == 3)
		{
			//Up line
			myGLCD.drawLine(X_Location-i ,(Y_Location+i) ,(X_Location+X_Size+i) ,(Y_Location+i));
			myGLCD.drawLine(X_Location-i ,(Y_Location+Y_Size-i) ,(X_Location+X_Size+i) ,(Y_Location+Y_Size-i));
		}
		
		if (Display_Num >= 2 && Display_Num <= 6 || Display_Num >= 8)
		{
			//Middle line
			myGLCD.drawLine(X_Location-i ,(Y_Location+i+X_Size) ,(X_Location+X_Size+i) ,(Y_Location+i+X_Size));
			myGLCD.drawLine(X_Location-i ,(Y_Location+Y_Size-i+X_Size) ,(X_Location+X_Size+i) ,(Y_Location+Y_Size-i+X_Size));
		}
		
		if (Display_Num == 0 || Display_Num == 5 || Display_Num == 2 || Display_Num == 3 || Display_Num == 6 || Display_Num >= 8)
		{
			//Down line
			myGLCD.drawLine(X_Location-i ,(Y_Location+i+(X_Size*2)) ,(X_Location+X_Size+i) ,(Y_Location+i+(X_Size*2)));
			myGLCD.drawLine(X_Location-i ,(Y_Location+Y_Size-i+(X_Size*2)) ,(X_Location+(X_Size)+i) ,(Y_Location+Y_Size-i+(X_Size*2)));
		}
		
		if (Display_Num == 4 || Display_Num == 5 || Display_Num == 6 || Display_Num >= 8 || Display_Num == 0)
		{
			//Left Up line
			myGLCD.drawVLine(X_Location-i-Y_Size+4,(Y_Location+i+Y_Size/2+5) ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i-Y_Size+4,(Y_Location+i+Y_Size/2+5) ,(X_Size-Y_Size/2-i*2));
		}
		
		if (Display_Num == 6 || Display_Num == 0  || Display_Num == 8 || Display_Num == 2)
		{
			//Left Down line
			myGLCD.drawVLine(X_Location-i-Y_Size+(Y_Size/4),(Y_Location+i+Y_Size/2+5)+X_Size ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i-Y_Size+(Y_Size/4),(Y_Location+i+Y_Size/2+5)+X_Size ,(X_Size-Y_Size/2-i*2));
		}
		
		if (Display_Num >= 0 && Display_Num <= 4  || Display_Num >= 7)
		{
			//Right Up line
			myGLCD.drawVLine(X_Location-i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i+Y_Size/2+5) ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i+Y_Size/2+5) ,(X_Size-Y_Size/2-i*2));
		}
		
		if (Display_Num == 1 || Display_Num == 0  || Display_Num >= 4 || Display_Num == 3)
		{
			//Right Down line
			myGLCD.drawVLine(X_Location-i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i-(Y_Size/4)+Y_Size)+X_Size ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i-(Y_Size/4)+Y_Size)+X_Size ,(X_Size-Y_Size/2-i*2));
		}
		
		
	}
}

void Seven_Segment_1_3(unsigned char Size_1_To_5, word X_Location, word Y_Location, char Display_Num)
{
	unsigned char X_Size, Y_Size;
	if (Size_1_To_5 <= 0 || Size_1_To_5 > 5)
	{
		Size_1_To_5 = 0x01;
	}
	switch(Size_1_To_5)
	{
		case 1:X_Size = 10, Y_Size = 2; break;
		case 2:X_Size = 20, Y_Size = 4; break;
		case 3:X_Size = 28, Y_Size = 9; break;
		case 4:X_Size = 48, Y_Size = 13; break;
		case 5:X_Size = 70, Y_Size = 17; break;
	}
	for(word i = 0; i <= (Y_Size/2); i++)
	{
		
		myGLCD.setColor(255, 0, 0);
		
		if (Display_Num == 0 || Display_Num >= 5 || Display_Num == 2 || Display_Num == 3)
		{
			//Up line
			myGLCD.drawLine(X_Location-i ,(Y_Location+i) ,(X_Location+X_Size+i) ,(Y_Location+i));
			myGLCD.drawLine(X_Location-i ,(Y_Location+Y_Size-i) ,(X_Location+X_Size+i) ,(Y_Location+Y_Size-i));
		}
		
		if (Display_Num >= 2 && Display_Num <= 6 || Display_Num >= 8)
		{
			//Middle line
			myGLCD.drawLine(X_Location-i ,(Y_Location+i+X_Size) ,(X_Location+X_Size+i) ,(Y_Location+i+X_Size));
			myGLCD.drawLine(X_Location-i ,(Y_Location+Y_Size-i+X_Size) ,(X_Location+X_Size+i) ,(Y_Location+Y_Size-i+X_Size));
		}
		
		if (Display_Num == 0 || Display_Num == 5 || Display_Num == 2 || Display_Num == 3 || Display_Num == 6 || Display_Num >= 8)
		{
			//Down line
			myGLCD.drawLine(X_Location-i ,(Y_Location+i+(X_Size*2)) ,(X_Location+X_Size+i) ,(Y_Location+i+(X_Size*2)));
			myGLCD.drawLine(X_Location-i ,(Y_Location+Y_Size-i+(X_Size*2)) ,(X_Location+(X_Size)+i) ,(Y_Location+Y_Size-i+(X_Size*2)));
		}
		
		if (Display_Num == 4 || Display_Num == 5 || Display_Num == 6 || Display_Num >= 8 || Display_Num == 0)
		{
			//Left Up line
			myGLCD.drawVLine(X_Location-i-Y_Size+2,(Y_Location+i+Y_Size/2+2) ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i-Y_Size+2,(Y_Location+i+Y_Size/2+2) ,(X_Size-Y_Size/2-i*2));
		}
		
		if (Display_Num == 6 || Display_Num == 0  || Display_Num == 8 || Display_Num == 2)
		{
			//Left Down line
			myGLCD.drawVLine(X_Location-i-Y_Size+(Y_Size/4),(Y_Location+i+Y_Size/2+2)+X_Size ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i-Y_Size+(Y_Size/4),(Y_Location+i+Y_Size/2+2)+X_Size ,(X_Size-Y_Size/2-i*2));
		}
		
		if (Display_Num >= 0 && Display_Num <= 4  || Display_Num >= 7)
		{
			//Right Up line
			myGLCD.drawVLine(X_Location-i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i+Y_Size/2+3) ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i+Y_Size/2+3) ,(X_Size-Y_Size/2-i*2));
		}
		
		if (Display_Num == 1 || Display_Num == 0  || Display_Num >= 4 || Display_Num == 3)
		{
			//Right Down line
			myGLCD.drawVLine(X_Location-i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i-(Y_Size/4)+Y_Size)+X_Size ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i-(Y_Size/4)+Y_Size)+X_Size ,(X_Size-Y_Size/2-i*2));
		}
		
	}
}

void Seven_Segment_1_3_LCD_Fill(unsigned char Size_1_To_5, word X_Location, word Y_Location, char Display_Num)
{
	unsigned char X_Size, Y_Size;
	if (Size_1_To_5 <= 0 || Size_1_To_5 > 5)
	{
		Size_1_To_5 = 0x01;
	}
	switch(Size_1_To_5)
	{
		case 1:X_Size = 10, Y_Size = 2; break;
		case 2:X_Size = 20, Y_Size = 4; break;
		case 3:X_Size = 28, Y_Size = 9; break;
		case 4:X_Size = 48, Y_Size = 13; break;
		case 5:X_Size = 70, Y_Size = 17; break;
	}
	for(word i = 0; i <= (Y_Size/2); i++)
	{
		
		myGLCD.setColor(30, 0, 0);
		
		if (Display_Num == 1 || Display_Num == 4)
		{
			//Up line
			myGLCD.drawLine(X_Location-i ,(Y_Location+i) ,(X_Location+X_Size+i) ,(Y_Location+i));
			myGLCD.drawLine(X_Location-i ,(Y_Location+Y_Size-i) ,(X_Location+X_Size+i) ,(Y_Location+Y_Size-i));
		}
		
		if (Display_Num == 0 || Display_Num == 1 || Display_Num == 7)
		{
			//Middle line
			myGLCD.drawLine(X_Location-i ,(Y_Location+i+X_Size) ,(X_Location+X_Size+i) ,(Y_Location+i+X_Size));
			myGLCD.drawLine(X_Location-i ,(Y_Location+Y_Size-i+X_Size) ,(X_Location+X_Size+i) ,(Y_Location+Y_Size-i+X_Size));
		}
		
		if (Display_Num == 1 || Display_Num == 4 || Display_Num == 7)
		{
			//Down line
			myGLCD.drawLine(X_Location-i ,(Y_Location+i+(X_Size*2)) ,(X_Location+X_Size+i) ,(Y_Location+i+(X_Size*2)));
			myGLCD.drawLine(X_Location-i ,(Y_Location+Y_Size-i+(X_Size*2)) ,(X_Location+(X_Size)+i) ,(Y_Location+Y_Size-i+(X_Size*2)));
		}
		
		if (Display_Num == 1 || Display_Num == 2 || Display_Num == 3 || Display_Num == 7)
		{
			//Left Up line
			myGLCD.drawVLine(X_Location-i-Y_Size+2,(Y_Location+i+Y_Size/2+2) ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i-Y_Size+2,(Y_Location+i+Y_Size/2+2) ,(X_Size-Y_Size/2-i*2));
		}
		
		if (Display_Num == 1 || Display_Num >= 3  && Display_Num <= 5 || Display_Num == 7 || Display_Num == 9)
		{
			//Left Down line
			myGLCD.drawVLine(X_Location-i-Y_Size+(Y_Size/4),(Y_Location+i+Y_Size/2+2)+X_Size ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i-Y_Size+(Y_Size/4),(Y_Location+i+Y_Size/2+2)+X_Size ,(X_Size-Y_Size/2-i*2));
		}
		
		if (Display_Num == 5 || Display_Num == 6)
		{
			//Right Up line
			myGLCD.drawVLine(X_Location-i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i+Y_Size/2+3) ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i+Y_Size/2+3) ,(X_Size-Y_Size/2-i*2));
		}
		
		if (Display_Num == 2)
		{
			//Right Down line
			myGLCD.drawVLine(X_Location-i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i-(Y_Size/4)+Y_Size)+X_Size ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i-(Y_Size/4)+Y_Size)+X_Size ,(X_Size-Y_Size/2-i*2));
		}
		
	}
}

void Seven_Segment_4_5_LCD_Fill(unsigned char Size_1_To_5, word X_Location, word Y_Location, char Display_Num)
{
	unsigned char X_Size, Y_Size;
	if (Size_1_To_5 <= 0 || Size_1_To_5 > 5)
	{
		Size_1_To_5 = 0x01;
	}
	switch(Size_1_To_5)
	{
		case 1:X_Size = 10, Y_Size = 2; break;
		case 2:X_Size = 20, Y_Size = 4; break;
		case 3:X_Size = 28, Y_Size = 9; break;
		case 4:X_Size = 48, Y_Size = 13; break;
		case 5:X_Size = 70, Y_Size = 17; break;
	}
	for(word i = 0; i <= (Y_Size/2); i++)
	{
		myGLCD.setColor(30, 0, 0);
		
		if (Display_Num == 1 || Display_Num == 4)
		{
			//Up line
			myGLCD.drawLine(X_Location-i ,(Y_Location+i) ,(X_Location+X_Size+i) ,(Y_Location+i));
			myGLCD.drawLine(X_Location-i ,(Y_Location+Y_Size-i) ,(X_Location+X_Size+i) ,(Y_Location+Y_Size-i));
		}
		
		if (Display_Num == 0 || Display_Num == 1 || Display_Num == 7)
		{
			//Middle line
			myGLCD.drawLine(X_Location-i ,(Y_Location+i+X_Size) ,(X_Location+X_Size+i) ,(Y_Location+i+X_Size));
			myGLCD.drawLine(X_Location-i ,(Y_Location+Y_Size-i+X_Size) ,(X_Location+X_Size+i) ,(Y_Location+Y_Size-i+X_Size));
		}
		
		if (Display_Num == 1 || Display_Num == 4 || Display_Num == 7)
		{
			//Down line
			myGLCD.drawLine(X_Location-i ,(Y_Location+i+(X_Size*2)) ,(X_Location+X_Size+i) ,(Y_Location+i+(X_Size*2)));
			myGLCD.drawLine(X_Location-i ,(Y_Location+Y_Size-i+(X_Size*2)) ,(X_Location+(X_Size)+i) ,(Y_Location+Y_Size-i+(X_Size*2)));
		}
		
		if (Display_Num == 1 || Display_Num == 2 || Display_Num == 3 || Display_Num == 7)
		{
			//Left Up line
			myGLCD.drawVLine(X_Location-i-Y_Size+4,(Y_Location+i+Y_Size/2+5) ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i-Y_Size+4,(Y_Location+i+Y_Size/2+5) ,(X_Size-Y_Size/2-i*2));
		}
		
		if (Display_Num == 1 || Display_Num >= 3  && Display_Num <= 5 || Display_Num == 7 || Display_Num == 9)
		{
			//Left Down line
			myGLCD.drawVLine(X_Location-i-Y_Size+(Y_Size/4),(Y_Location+i+Y_Size/2+5)+X_Size ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i-Y_Size+(Y_Size/4),(Y_Location+i+Y_Size/2+5)+X_Size ,(X_Size-Y_Size/2-i*2));
		}
		
		if (Display_Num == 5 || Display_Num == 6)
		{
			//Right Up line
			myGLCD.drawVLine(X_Location-i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i+Y_Size/2+5) ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i+Y_Size/2+5) ,(X_Size-Y_Size/2-i*2));
		}
		
		if (Display_Num == 2)
		{
			//Right Down line
			myGLCD.drawVLine(X_Location-i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i-(Y_Size/4)+Y_Size)+X_Size ,(X_Size-Y_Size/2-i*2));
			myGLCD.drawVLine(X_Location+i+Y_Size-(Y_Size/4)+X_Size,(Y_Location+i-(Y_Size/4)+Y_Size)+X_Size ,(X_Size-Y_Size/2-i*2));
		}
		
		
	}
	
}

void Main_Seven_Segment(unsigned char Size_1_To_5, word X_Location, word Y_Location, char Display_Num)
{
	unsigned char X_Size, Y_Size;
	if (Size_1_To_5 <= 0 || Size_1_To_5 > 5)
	{
		Size_1_To_5 = 0x01;
	}
	switch(Size_1_To_5)
	{
		case 1:X_Size = 10, Y_Size = 2; break;
		case 2:X_Size = 20, Y_Size = 4; break;
		case 3:X_Size = 28, Y_Size = 9; break;
		case 4:X_Size = 48, Y_Size = 13; break;
		case 5:X_Size = 70, Y_Size = 17; break;
	}
	if (Size_1_To_5 > 3)
	{
		Seven_Segment_4_5(Size_1_To_5,X_Location,Y_Location,Display_Num);
	}
	else if (Size_1_To_5 < 4)
	{
		Seven_Segment_1_3(Size_1_To_5,X_Location,Y_Location,Display_Num);
	}
	
	//Fill the line that not working
	
	if (Size_1_To_5 > 3)
	{
		Seven_Segment_4_5_LCD_Fill(Size_1_To_5,X_Location,Y_Location, Display_Num);
	}
	else if (Size_1_To_5 < 4)
	{
		Seven_Segment_1_3_LCD_Fill(Size_1_To_5,X_Location,Y_Location,Display_Num);
	}
}

void Battery(unsigned char Capacity_in_Precent)
{
	char Fill_value;
	unsigned char Car[] ={
		0x3F, 0x80,  // ..#######.......
		0x71, 0x40,  // .###...#.#......
		0xE1, 0x20,  // ###....#..#.....
		0xF1, 0x1C,  // ####...#...###..
		0xFF, 0xFE,  // ###############.
		0xC7, 0xC7,  // ##...#####...###
		0x93, 0x93,  // #..#..###..#..##
		0xBB, 0xBB,  // #.###.###.###.##
		0x10, 0x10,  // ...#.......#....
		0x00, 0x00,  // ................
		0x00, 0x00,  // ................
		0x00, 0x00,  // ................
		0x00, 0x00,  // ................
		0x00, 0x00,  // ................
		0x00, 0x00,  // ................
		0x00, 0x00,  // ................
	};
	
	
	//Print The car symbol
	Print_Letter_16_Bit(Car,100,17);
	
	//background fill
	//It is the same buttery just a background to make it structure
	for (char i = 0; i < 2; i++)
	{
		myGLCD.setColor(64,64,64);
		myGLCD.drawHLine(13,9+i,3);
	}
	for (char i = 0; i < 18; i++)
	{
		myGLCD.setColor(64,64,64);
		myGLCD.drawHLine(8,11+i,13);
	}
	
	//Real value
	if (Capacity_in_Precent > 90)
	{
		
		if (Capacity_in_Precent > 90 && Capacity_in_Precent < 95)
		{
			Fill_value = 0;
		}
		else
		{
			Fill_value = 1;
		}
		for (; Fill_value < 2; Fill_value++)
		{
			myGLCD.setColor(255,255,255);
			myGLCD.drawHLine(13,9+Fill_value,3);
		}
		Fill_value = 0;
	}
	
	if (Capacity_in_Precent >= 85 && Capacity_in_Precent <= 90)
	{
		Fill_value = 1;
	}
	else if (Capacity_in_Precent <=85 && Capacity_in_Precent >= 80)
	{
		Fill_value = 2;
	}
	else if (Capacity_in_Precent <=80 && Capacity_in_Precent >= 75)
	{
		Fill_value = 3;
	}
	else if (Capacity_in_Precent <=75 && Capacity_in_Precent >= 70)
	{
		Fill_value = 4;
	}
	else if (Capacity_in_Precent <=70 && Capacity_in_Precent >= 60)
	{
		Fill_value = 5;
	}
	else if (Capacity_in_Precent <=60 && Capacity_in_Precent >= 55)
	{
		Fill_value = 6;
	}
	else if (Capacity_in_Precent <=55 && Capacity_in_Precent >= 50)
	{
		Fill_value = 7;
	}
	else if (Capacity_in_Precent <=50 && Capacity_in_Precent >= 45)
	{
		Fill_value = 8;
	}
	else if (Capacity_in_Precent <=45 && Capacity_in_Precent >= 40)
	{
		Fill_value = 9;
	}
	else if (Capacity_in_Precent <=40 && Capacity_in_Precent >= 35)
	{
		Fill_value = 10;
	}
	else if (Capacity_in_Precent <=35 && Capacity_in_Precent >= 30)
	{
		Fill_value = 11;
	}
	else if (Capacity_in_Precent <=30 && Capacity_in_Precent >= 25)
	{
		Fill_value = 12;
	}
	else if (Capacity_in_Precent <=25 && Capacity_in_Precent >= 20)
	{
		Fill_value = 13;
	}
	else if (Capacity_in_Precent <=20 && Capacity_in_Precent >= 15)
	{
		Fill_value = 14;
	}
	else if (Capacity_in_Precent <=15 && Capacity_in_Precent >= 10)
	{
		Fill_value = 15;
	}
	else if (Capacity_in_Precent <=10 && Capacity_in_Precent >= 0)
	{
		Fill_value = 16;
	}
	for (; Fill_value < 18; Fill_value++)
	{
		myGLCD.setColor(255,255,255);
		myGLCD.drawHLine(8,11+Fill_value,13);
	}
	if (Capacity_in_Precent > 99)
	{
		myGLCD.printChar('1', 28,14);
		myGLCD.printChar('0',42,14);
		myGLCD.printChar('0',56,14);
		myGLCD.printChar('%',70,14);
	}
	else
	{
		myGLCD.printChar(Capacity_in_Precent/10+0x30, 28,14);
		myGLCD.printChar(Capacity_in_Precent%10+0x30,42,14);
		myGLCD.printChar('%',56,14);
		myGLCD.printChar(' ',70,14);

	}
}

void Print_Letter_16_Bit(unsigned char *Bit_value,word X,word Y)
{

	for (char i = 0; i < 32; i+=2)
	{
		for (char bit_1_OR_0 = 0; bit_1_OR_0 <= 7; bit_1_OR_0++)
		{
			if (Bit_value[i+1] & (1 << bit_1_OR_0))
			{
				myGLCD.drawPixel(X-(bit_1_OR_0),Y+i/2);
			}
		}
		
		for (char bit_1_OR_0 = 7; bit_1_OR_0 <= 15; bit_1_OR_0++)
		{
			if (Bit_value[i] & (1 << (bit_1_OR_0-7)))
			{
				myGLCD.drawPixel(X-(bit_1_OR_0),Y+i/2);
			}
		}
	}
}

void Hebrew_Letters_Big_Size(word Letter_Num, word X_Location,word Y_Location)
{
	//16*16
	//The letters Numbers Based on GEOMATRIA numbers
	//à=1, á=2ú â=3, ã=4, ä=5, å=5, æ=6, ç=8, è=9, é=10, ë=20, ì=30, î=40, ð=50, ñ=60, ò=70, ô=80, ö=90, ÷=100,ø=200, ù=300, ú=400
	//ê=21, í=41, ï=51, ó=81, õ=91
	//Space = 0x30;
	switch(Letter_Num)
	{
		case 1:
		{
			unsigned char _1[]{
				/* character 0x00E0 ('à'): [width=16, offset= 0x1190 (4496) ] */
				0xF8, 0x1E,  // #####......####.
				0x7C, 0x1E,  // .#####.....####.
				0x3C, 0x1E,  // ..####.....####.
				0x3E, 0x1E,  // ..#####....####.
				0x1F, 0x1C,  // ...#####...###..
				0x1F, 0x3C,  // ...#####..####..
				0x3F, 0xFC,  // ..############..
				0x7F, 0xF8,  // .############...
				0xFF, 0xF8,  // #############...
				0xF8, 0x78,  // #####....####...
				0xF8, 0x7C,  // #####....#####..
				0xF8, 0x3C,  // #####.....####..
				0xF8, 0x3E,  // #####.....#####.
				0xF8, 0x1F,  // #####......#####
				0x00, 0x00,  // ................
				0x00, 0x00,  // ................

			};
			Print_Letter_16_Bit(_1, X_Location, Y_Location);
			break;
		}
		case 2:
		{
			unsigned char _2[]={
				/* character 0x00E1 ('á'): [width=16, offset= 0x11B0 (4528) ] */
				0x7F, 0x80,  // .########.......
				0x7F, 0xE0,  // .##########.....
				0x7F, 0xF0,  // .###########....
				0x01, 0xF0,  // .......#####....
				0x00, 0xF8,  // ........#####...
				0x00, 0x78,  // .........####...
				0x00, 0x78,  // .........####...
				0x00, 0x78,  // .........####...
				0x00, 0x78,  // .........####...
				0x00, 0x78,  // .........####...
				0x00, 0x78,  // .........####...
				0x7F, 0xFF,  // .###############
				0x7F, 0xFF,  // .###############
				0x7F, 0xFF,  // .###############
				0x00, 0x00,  // ................
			0x00, 0x00}; // ................
			Print_Letter_16_Bit(_2, X_Location, Y_Location);
			break;
		}
		case 3:
		{
			unsigned char _3[]={
				/* character 0x00E2 ('â'): [width=16, offset= 0x11D0 (4560) ] */
				0x0F, 0x80,  // ....#####.......
				0x0F, 0xE0,  // ....#######.....
				0x0F, 0xE0,  // ....#######.....
				0x01, 0xF0,  // .......#####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x03, 0xF0,  // ......######....
				0x07, 0xF0,  // .....#######....
				0x0F, 0xF0,  // ....########....
				0x1E, 0x78,  // ...####..####...
				0x1E, 0x78,  // ...####..####...
				0x3C, 0x78,  // ..####...####...
				0x00, 0x00,  // ................
				0x00, 0x00,  // ................
			};
			Print_Letter_16_Bit(_3, X_Location, Y_Location);
			break;
		}
		case 4:
		{
			unsigned char _4[]={
				/* character 0x00E3 ('ã'): [width=16, offset= 0x11F0 (4592) ] */
				0xFF, 0xFF,  // ################
				0xFF, 0xFF,  // ################
				0xFF, 0xFF,  // ################
				0x00, 0x3C,  // ..........####..
				0x00, 0x3C,  // ..........####..
				0x00, 0x3C,  // ..........####..
				0x00, 0x3C,  // ..........####..
				0x00, 0x3C,  // ..........####..
				0x00, 0x3C,  // ..........####..
				0x00, 0x3C,  // ..........####..
				0x00, 0x3C,  // ..........####..
				0x00, 0x3C,  // ..........####..
				0x00, 0x3C,  // ..........####..
				0x00, 0x3C,  // ..........####..
				0x00, 0x00,  // ................
				0x00, 0x00,  // ................
			};
			Print_Letter_16_Bit(_4, X_Location, Y_Location);
			break;
		}
		case 5:
		{
			unsigned char _5[]={
				/* character 0x00E4 ('ä'): [width=16, offset= 0x1210 (4624) ] */
				0xFF, 0xC0,  // ##########......
				0xFF, 0xF0,  // ############....
				0xFF, 0xF8,  // #############...
				0x00, 0xF8,  // ........#####...
				0x00, 0x7C,  // .........#####..
				0x00, 0x3C,  // ..........####..
				0x00, 0x3C,  // ..........####..
				0x00, 0x3C,  // ..........####..
				0xF0, 0x3C,  // ####......####..
				0xF0, 0x3C,  // ####......####..
				0xF0, 0x3C,  // ####......####..
				0xF0, 0x3C,  // ####......####..
				0xF0, 0x3C,  // ####......####..
				0xF0, 0x3C,  // ####......####..
				0x00, 0x00,  // ................
				0x00, 0x00,  // ................
			};
			Print_Letter_16_Bit(_5, X_Location, Y_Location);
			break;
		}
		case 6:
		{
			unsigned char _6[]={
				
				/* character 0x00E5 ('å'): [width=9, offset= 0x1230 (4656) ] */
				0x00, 0x78,  // .####....
				0x00, 0x7C,  // .#####...
				0x00, 0x7E,  // .######..
				0x00, 0x7E,  // .######..
				0x00, 0x1E,  // ...####..
				0x00, 0x1E,  // ...####..
				0x00, 0x1E,  // ...####..
				0x00, 0x1E,  // ...####..
				0x00, 0x1E,  // ...####..
				0x00, 0x1E,  // ...####..
				0x00, 0x1E,  // ...####..
				0x00, 0x1E,  // ...####..
				0x00, 0x1E,  // ...####..
				0x00, 0x1E,  // ...####..
				0x00, 0x00,  // .........
				0x00, 0x00,  // .........
			};
			Print_Letter_16_Bit(_6, X_Location, Y_Location);
			break;
		}
		case 7:
		{
			unsigned char _7[]={
				
				/* character 0x00E6 ('æ'): [width=10, offset= 0x1250 (4688) ] */
				0x03, 0xFF,  // ......##########
				0x03, 0xFF,  // ......##########
				0x03, 0xFF,  // ......##########
				0x00, 0x3C,  // ..........####..
				0x00, 0x78,  // .........####...
				0x00, 0x70,  // .........###....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x00, 0x00,  // ................
				0x00, 0x00,  // ................
			};
			Print_Letter_16_Bit(_7, X_Location, Y_Location);
			break;
		}
		case 8:
		{
			unsigned char _8[]={
				
				/* character 0x00E7 ('ç'): [width=15, offset= 0x1270 (4720) ] */
				0xFF, 0x80,  // #########......
				0xFF, 0xE0,  // ###########....
				0xFF, 0xF0,  // ############...
				0xF0, 0xF0,  // ####....####...
				0xF0, 0x78,  // ####.....####..
				0xF0, 0x78,  // ####.....####..
				0xF0, 0x78,  // ####.....####..
				0xF0, 0x78,  // ####.....####..
				0xF0, 0x78,  // ####.....####..
				0xF0, 0x78,  // ####.....####..
				0xF0, 0x78,  // ####.....####..
				0xF0, 0x78,  // ####.....####..
				0xF0, 0x78,  // ####.....####..
				0xF0, 0x78,  // ####.....####..
				0x00, 0x00,  // ...............
				0x00, 0x00,  // ...............
			};
			Print_Letter_16_Bit(_8, X_Location, Y_Location);
			break;
		}
		case 9:
		{
			unsigned char _9[]={
				
				/* character 0x00E8 ('è'): [width=14, offset= 0x1290 (4752) ] */
				0xE1, 0xE0,  // ###....####...
				0xF3, 0xF0,  // ####..######..
				0xF3, 0xF0,  // ####..######..
				0xF3, 0x78,  // ####..##.####.
				0xF0, 0x78,  // ####.....####.
				0xF0, 0x78,  // ####.....####.
				0xF0, 0x78,  // ####.....####.
				0xF0, 0x78,  // ####.....####.
				0xF0, 0x78,  // ####.....####.
				0xF0, 0x78,  // ####.....####.
				0xF0, 0x78,  // ####.....####.
				0x78, 0xF0,  // .####...####..
				0x7F, 0xF0,  // .###########..
				0x3F, 0xE0,  // ..#########...
				0x0F, 0x80,  // ....#####.....
				0x00, 0x00,  // ..............
			};
			Print_Letter_16_Bit(_9, X_Location, Y_Location);
			break;
		}
		case 10:
		{
			unsigned char _10[]={
				
				/* character 0x00E9 ('é'): [width=5, offset= 0x12B0 (4784) ] */
				0x00, 0x78, // .####
				0x00, 0x78, // .####
				0x00, 0x78, // .####
				0x00, 0x78, // .####
				0x00, 0x78, // .####
				0x00, 0x78, // .####
				0x00, 0x78, // .####
				0x00, 0x78, // .####
				0x00, 0x78, // .####
				0x00, 0x00, // .....
				0x00, 0x00, // .....
				0x00, 0x00, // .....
				0x00, 0x00, // .....
				0x00, 0x00, // .....
				0x00, 0x00, // .....
				0x00, 0x00, // .....
			};
			Print_Letter_16_Bit(_10, X_Location, Y_Location);
			break;
		}
		case 20:
		{
			unsigned char _20[]={
				
				/* character 0x00EB ('ë'): [width=14, offset= 0x12E0 (4832) ] */
				0xFF, 0x00,  // ########......
				0xFF, 0xC0,  // ##########....
				0x7F, 0xE0,  // .##########...
				0x03, 0xE0,  // ......#####...
				0x00, 0xF0,  // ........####..
				0x00, 0xF0,  // ........####..
				0x00, 0xF0,  // ........####..
				0x00, 0xF0,  // ........####..
				0x00, 0xF0,  // ........####..
				0x00, 0xF0,  // ........####..
				0x01, 0xF0,  // .......#####..
				0x03, 0xE0,  // ......#####...
				0x7F, 0xE0,  // .##########...
				0xFF, 0xC0,  // ##########....
				0xFF, 0x00,  // ########......
				0x00, 0x00,  // ..............
			};
			Print_Letter_16_Bit(_20, X_Location, Y_Location);
			break;
		}
		case 30:
		{
			unsigned char _30[]={
				
				/* character 0x00EC ('ì'): [width=14, offset= 0x1300 (4864) ] */
				0xF0, 0x00,  // ####..........
				0xF0, 0x00,  // ####..........
				0xF0, 0x00,  // ####..........
				0xF0, 0x00,  // ####..........
				0xFF, 0xF0,  // ############..
				0xFF, 0xF0,  // ############..
				0xFF, 0xF0,  // ############..
				0x00, 0xF0,  // ........####..
				0x00, 0xF0,  // ........####..
				0x00, 0xF0,  // ........####..
				0x00, 0xF0,  // ........####..
				0x01, 0xE0,  // .......####...
				0x01, 0xE0,  // .......####...
				0x03, 0xC0,  // ......####....
				0x03, 0xC0,  // ......####....
				0x03, 0xC0,  // ......####....
			};
			Print_Letter_16_Bit(_30, X_Location, Y_Location);
			break;
		}
		case 40:
		{
			unsigned char _40[]={
				
				/* character 0x00EE ('î'): [width=15, offset= 0x1340 (4928) ] */
				0xF0, 0xF0,  // ####....####...
				0x73, 0xF8,  // .###..#######..
				0x7F, 0xFC,  // .#############.
				0x7F, 0x3C,  // .#######..####.
				0x3E, 0x1E,  // ..#####....####
				0x3E, 0x1E,  // ..#####....####
				0x3C, 0x1E,  // ..####.....####
				0x1C, 0x1E,  // ...###.....####
				0x3c, 0x1E,  // ..####.....####
				0x3C, 0x1E,  // ..####.....####
				0x3C, 0x1E,  // ..####.....####
				0x3C, 0x1E,  // ..####.....####
				0x78, 0xFE,  // .####...#######
				0x78, 0xFE,  // .####...#######
				0x78, 0xFE,  // .####...#######
				0x00, 0x00,  // ...............
			};
			Print_Letter_16_Bit(_40, X_Location, Y_Location);
			break;
		}
		case 50:
		{
			unsigned char _50[]={
				/* character 0x00F0 ('ð'): [width=16, offset= 0x1380 (4992) ] */
				0x00, 0x7C,  // .........#####..
				0x00, 0x7E,  // .........######.
				0x00, 0x7F,  // .........#######
				0x00, 0x1F,  // ...........#####
				0x00, 0x0F,  // ............####
				0x00, 0x0F,  // ............####
				0x00, 0x0F,  // ............####
				0x00, 0x0F,  // ............####
				0x00, 0x0F,  // ............####
				0x00, 0x0F,  // ............####
				0x00, 0x0F,  // ............####
				0x00, 0x7F,  // .........#######
				0x00, 0x7F,  // .........#######
				0x00, 0x7F,  // .........#######
				0x00, 0x00,  // ................
				0x00, 0x00,  // ................
			};
			Print_Letter_16_Bit(_50, X_Location, Y_Location);
			break;
		}
		case 60:
		{
			unsigned char _60[]={
				/* character 0x00F1 ('ñ'): [width=16, offset= 0x13A0 (5024) ] */
				0x07, 0x80,  // .....####.......
				0x1F, 0xE0,  // ...########.....
				0x3F, 0xF0,  // ..##########....
				0x7F, 0xF8,  // .############...
				0xF8, 0x7C,  // #####....#####..
				0xF0, 0x3C,  // ####......####..
				0xF0, 0x3C,  // ####......####..
				0xF0, 0x3C,  // ####......####..
				0xF0, 0x3C,  // ####......####..
				0xF8, 0x7C,  // #####....#####..
				0x7F, 0xF8,  // .############...
				0x3F, 0xF0,  // ..##########....
				0x1F, 0xE0,  // ...########.....
				0x07, 0x80,  // .....####.......
				0x00, 0x00,  // ................
				0x00, 0x00,  // ................
			};
			Print_Letter_16_Bit(_60, X_Location, Y_Location);
			break;
		}
		case 70:
		{
			unsigned char _70[]={
				/* character 0x00F2 ('ò'): [width=15, offset= 0x13C0 (5056) ] */
				0x78, 0x1E,  // .####......####
				0x78, 0x1E,  // .####......####
				0x7C, 0x1E,  // .#####.....####
				0x3C, 0x1E,  // ..####.....####
				0x3C, 0x1E,  // ..####.....####
				0x3C, 0x1E,  // ..####.....####
				0x3C, 0x1E,  // ..####.....####
				0x3E, 0x1E,  // ..#####....####
				0x1E, 0x1E,  // ...####....####
				0x1E, 0x3C,  // ...####...####.
				0x1E, 0x3C,  // ...####...####.
				0x1E, 0x3C,  // ...####...####.
				0x3F, 0xFC,  // ..############.
				0xFF, 0xF8,  // #############..
				0xFF, 0xE0,  // ###########....
				0xE0, 0x00,  // ###............
			};
			Print_Letter_16_Bit(_70, X_Location, Y_Location);
			break;
		}
		case 80:
		{
			unsigned char _80[]={
				/* character 0x00F4 ('ô'): [width=14, offset= 0x1400 (5120) ] */
				0x3F, 0x80,  // ..#######.....
				0xFF, 0xE0,  // ###########...
				0xFF, 0xF0,  // ############..
				0xF0, 0xF8,  // ####....#####.
				0xF0, 0x78,  // ####.....####.
				0xF0, 0x3C,  // ####......####
				0xFC, 0x3C,  // ######....####
				0x7E, 0x3C,  // .######...####
				0x00, 0x3C,  // ..........####
				0x00, 0x3C,  // ..........####
				0x00, 0x3C,  // ..........####
				0x40, 0x78,  // .#.......####.
				0xFF, 0xF8,  // #############.
				0xFF, 0xF0,  // ############..
				0x3F, 0x80,  // ..#######.....
				0x00, 0x00,  // ..............
			};
			Print_Letter_16_Bit(_80, X_Location, Y_Location);
			break;
		}
		case 90:
		{
			unsigned char _90[]={
				/* character 0x00F6 ('ö'): [width=15, offset= 0x1440 (5184) ] */
				0xF8, 0x3C,  // #####.....####.
				0x78, 0x3C,  // .####.....####.
				0x3C, 0x3C,  // ..####....####.
				0x3E, 0x3C,  // ..#####...####.
				0x1E, 0x3C,  // ...####...####.
				0x1F, 0x3C,  // ...#####..####.
				0x0F, 0xF8,  // ....#########..
				0x07, 0xF0,  // .....#######...
				0x07, 0xF0,  // .....#######...
				0x03, 0xF0,  // ......######...
				0x01, 0xF0,  // .......#####...
				0x01, 0xF8,  // .......######..
				0xFF, 0xF8,  // #############..
				0xFF, 0xFC,  // ##############.
				0xFF, 0xFC,  // ##############.
				0x00, 0x00,  // ...............
			};
			Print_Letter_16_Bit(_90, X_Location, Y_Location);
			break;
		}
		case 100:
		{
			unsigned char _100[]={
				/* character 0x00F7 ('÷'): [width=15, offset= 0x1460 (5216) ] */
				0xFF, 0xFC,  // ##############.
				0xFF, 0xFC,  // ##############.
				0xFF, 0xFC,  // ##############.
				0x00, 0x3C,  // ..........####.
				0x00, 0x3C,  // ..........####.
				0x00, 0x3C,  // ..........####.
				0x00, 0x78,  // .........####..
				0xF0, 0x78,  // ####.....####..
				0xF0, 0xE8,  // ####....#####..
				0xF1, 0xF0,  // ####...#####...
				0xF1, 0xE0,  // ####...####....
				0xF1, 0xE0,  // ####...####....
				0xF1, 0xE0,  // ####...####....
				0xF0, 0x00,  // ####...........
				0xF0, 0x00,  // ####...........
				0xF0, 0x00,  // ####...........
			};
			Print_Letter_16_Bit(_100, X_Location, Y_Location);
			break;
		}
		case 200:
		{
			unsigned char _200[]={
				/* character 0x00F8 ('ø'): [width=16, offset= 0x1480 (5248) ] */
				0xFF, 0x80,  // #########.......
				0xFF, 0xE0,  // ###########.....
				0xFF, 0xF0,  // ############....
				0x01, 0xF0,  // .......#####....
				0x00, 0x78,  // .........####...
				0x00, 0x78,  // .........####...
				0x00, 0x78,  // .........####...
				0x00, 0x78,  // .........####...
				0x00, 0x78,  // .........####...
				0x00, 0x78,  // .........####...
				0x00, 0x78,  // .........####...
				0x00, 0x78,  // .........####...
				0x00, 0x78,  // .........####...
				0x00, 0x78,  // .........####...
				0x00, 0x00,  // ................
				0x00, 0x00,  // ................
			};
			Print_Letter_16_Bit(_200, X_Location, Y_Location);
			break;
		}
		case 300:
		{
			unsigned char _300[]={
				/* character 0x00F9 ('ù'): [width=14, offset= 0x14A0 (5280) ] */
				0xE3, 0x9C,  // ###...###..###
				0xE3, 0x9C,  // ###...###..###
				0xE3, 0x9C,  // ###...###..###
				0xE7, 0x9C,  // ###..####..###
				0xEF, 0x9C,  // ###.#####..###
				0xFF, 0x1C,  // ########...###
				0xFE, 0x1C,  // #######....###
				0xFC, 0x1C,  // ######.....###
				0xF8, 0x3C,  // #####.....####
				0xE0, 0x7C,  // ###......#####
				0xFF, 0xFC,  // ##############
				0xFF, 0xF8,  // #############.
				0x7F, 0xF0,  // .###########..
				0x3F, 0xC0,  // ..########....
				0x00, 0x00,  // ..............
				0x00, 0x00,  // ..............
			};
			Print_Letter_16_Bit(_300, X_Location, Y_Location);
			break;
		}
		case 400:
		{
			unsigned char _400[]={
				/* character 0x00FA ('ú'): [width=16, offset= 0x14C0 (5312) ] */
				0xFF, 0xF0,  // ############....
				0xFF, 0xFC,  // ##############..
				0xFF, 0xFE,  // ###############.
				0x1E, 0x1F,  // ...####....#####
				0x1E, 0x0F,  // ...####.....####
				0x1E, 0x0F,  // ...####.....####
				0x1E, 0x0F,  // ...####.....####
				0x1E, 0x0F,  // ...####.....####
				0x1E, 0x0F,  // ...####.....####
				0x1E, 0x0F,  // ...####.....####
				0x1E, 0x0F,  // ...####.....####
				0x1E, 0x0F,  // ...####.....####
				0x7E, 0x0F,  // .######.....####
				0xFE, 0x0F,  // #######.....####
				0x7C, 0x0F,  // .#####......####
				0x00, 0x00,  // ................
			};
			Print_Letter_16_Bit(_400, X_Location, Y_Location);
			break;
		}
		case 21:
		{
			unsigned char _21[]={
				
				/* character 0x00EA ('ê'): [width=14, offset= 0x12C0 (4800) ] */
				0xFE, 0x00,  // #######.......
				0xFF, 0x80,  // #########.....
				0xFF, 0xC0,  // ##########....
				0x07, 0xC0,  // .....#####....
				0x03, 0xE0,  // ......#####...
				0x01, 0xE0,  // .......####...
				0x01, 0xE0,  // .......####...
				0x01, 0xE0,  // .......####...
				0x01, 0xE0,  // .......####...
				0x01, 0xE0,  // .......####...
				0x01, 0xE0,  // .......####...
				0x01, 0xE0,  // .......####...
				0x01, 0xE0,  // .......####...
				0x01, 0xE0,  // .......####...
				0x01, 0xE0,  // .......####...
				0x01, 0xE0,  // .......####...
			};
			Print_Letter_16_Bit(_21, X_Location, Y_Location);
			break;
		}
		case 41:
		{
			unsigned char _41[]={
				/* character 0x00ED ('í'): [width=15, offset= 0x1320 (4896) ] */
				0xFF, 0xE0,  // ###########....
				0xFF, 0xF8,  // #############..
				0xFF, 0xFC,  // ##############.
				0xF0, 0x3C,  // ####......####.
				0xF0, 0x1E,  // ####.......####
				0xF0, 0x1E,  // ####.......####
				0xF0, 0x1E,  // ####.......####
				0xF0, 0x1E,  // ####.......####
				0xF0, 0x1E,  // ####.......####
				0xF0, 0x1E,  // ####.......####
				0xF0, 0x1E,  // ####.......####
				0xFF, 0xFE,  // ###############
				0xFF, 0xFE,  // ###############
				0xFF, 0xFE,  // ###############
				0x00, 0x00,  // ...............
				0x00, 0x00,  // ...............
			};
			Print_Letter_16_Bit(_41, X_Location, Y_Location);
			break;
		}
		case 51:
		{
			unsigned char _51[]={
				/* character 0x00EF ('ï'): [width=10, offset= 0x1360 (4960) ] */
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
				0xF0, 0x00,  // ####......
			};
			Print_Letter_16_Bit(_51, X_Location, Y_Location);
			break;
		}
		case 81:
		{
			unsigned char _81[]={
				/* character 0x00F3 ('ó'): [width=16, offset= 0x13E0 (5088) ] */
				0xFF, 0x00,  // ########........
				0xFF, 0xC0,  // ##########......
				0xFF, 0xE0,  // ###########.....
				0xE1, 0xF0,  // ###....#####....
				0xE0, 0xF0,  // ###.....####....
				0xE0, 0xF0,  // ###.....####....
				0xF0, 0xF0,  // ####....####....
				0x7C, 0xF0,  // .#####..####....
				0x3C, 0xF0,  // ..####..####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
				0x00, 0xF0,  // ........####....
			};
			Print_Letter_16_Bit(_81, X_Location, Y_Location);
			break;
		}
		case 91:
		{
			unsigned char _91[]={
				/* character 0x00F5 ('õ'): [width=15, offset= 0x1420 (5152) ] */
				0xF0, 0x78,  // ####.....####..
				0x78, 0x78,  // .####....####..
				0x78, 0x78,  // .####....####..
				0x3C, 0x78,  // ..####...####..
				0x3C, 0x78,  // ..####...####..
				0x1F, 0xF0,  // ...#########...
				0x1F, 0xF0,  // ...#########...
				0x0F, 0xE0,  // ....#######....
				0x0F, 0xE0,  // ....######.....
				0x0F, 0x80,  // ....#####......
				0x0F, 0x00,  // ....####.......
				0x0F, 0x00,  // ....####.......
				0x0F, 0x00,  // ....####.......
				0x0F, 0x00,  // ....####.......
				0x0F, 0x00,  // ....####.......
				0x0F, 0x00,  // ....####.......
			};
			Print_Letter_16_Bit(_91, X_Location, Y_Location);
			break;
		}
		case 0x30:
		{
			unsigned char _0x30[]={
				
				/* character 0x00E9 (' '): [width=5, offset= 0x12B0 (4784) ] */
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
			};
			Print_Letter_16_Bit(_0x30, X_Location, Y_Location);
			break;
		}
	}
}

void Print_Hebrew_String(word *Hebrew_String, word X_location, word Y_Location, unsigned char Size_String)
{
	static char Size;
	Font_Size = &Size;
	
	X_location = 480 - X_location;
	while(Size_String)
	{
		Size_String--;
		if (*Hebrew_String != 30)
		{
			if (Size == Big)
			{
				Hebrew_Letters_Big_Size(*Hebrew_String, X_location, Y_Location);
			}
			else if (Size == Medium && *Hebrew_String != 3)
			{
				Hebrew_Letters_Medium_Size(*Hebrew_String, X_location, Y_Location);
			}
			
		}
		
		switch (*Hebrew_String)
		{
			
			case 3:
			{
				if (Size == Medium)
				{
					Hebrew_Letters_Medium_Size(*Hebrew_String, X_location-2, Y_Location);
					X_location -= 6;
					break;
				}
				else if (Size == Small)
				{
					X_location += 1;
					break;
				}
			}
			case 1:
			case 2:
			case 4:
			case 5:
			case 8:
			case 9:
			case 20:
			case 40:
			case 60:
			case 70:
			case 80:
			case 90:
			case 100:
			case 200:
			case 300:
			case 400:
			case 21:
			case 41:
			case 81:
			case 91:
			case 0x30:
			{
				if (Size == Big)
				{
					X_location -= 17;
				}
				else if (Size == Medium)
				{
					X_location -= 13;
				}
				else if (Size == Small)
				{
					X_location -= 8;
				}
				
				break;
			}
			case 10:
			{
				if (Size == Medium)
				{
					X_location -= 3;
					break;
				}
				else if (Size == Small)
				{
					X_location -= 2;
					break;
				}
				
			}
			case 6:
			case 7:
			
			{
				if (Size == Medium)
				{
					X_location -= 6;
					break;
				}
				else if (Size == Small)
				{
					X_location -= 3;
					break;
				}
				
			}
			case 50:
			{
				if (Size == Medium)
				{
					X_location -= 6;
					break;
				}
				else if (Size == Small)
				{
					X_location -= 4;
					break;
				}
				
			}
			case 51:
			{
				if (Size == Big)
				{
					X_location -= 10;
				}
				else if (Size == Medium)
				{
					X_location -= 8;
				}
				else if (Size == Small)
				{
					X_location -= 6;
				}
				
				break;
			}
			
			case 30:
			{
				if (Size == Big)
				{
					Hebrew_Letters_Big_Size(*Hebrew_String, X_location, Y_Location-4);
					X_location -= 17;
				}
				else if (Size == Medium)
				{
					Hebrew_Letters_Medium_Size(*Hebrew_String, X_location, Y_Location);
					X_location -= 12;
				}
				else if (Size == Small)
				{
					X_location -= 8;
				}
				break;
			}
		}
		
		Hebrew_String++;
	}
}

void Line_With_angle(word X_Location, word Y_Location, word Line_Size, word Line_angle)
{
	//in this function we have 4 condition X&Y positive OR X&Y negative
	//OR X=Positive Y=Negative OR X=Negative  Y=Positive, there is an if statment that fix it
	//in addition we have caculate bt tri-angle to set End point of the line.
	
	//the end of the line, the line start from X.Y Location
	word X_End_Point, Y_End_Point;
	
	//Because i convert From Radians to degrees i use Double to keep aqurecy
	double angle = Line_angle;
	
	//The function get only RADIANS so i convert it to Degrees
	angle *= PI/180;
	
	//
	//					  ...
	//					..	.
	//                ..	.
	//              ..		.
	//            ..		.
	//       C  ..			.  B
	//        ..			.
	//      ..				.
	//    ..				.
	//  ..degrees			.
	//  .....................
	//				A
	
	//get X end Point by the formula of sin(degrees)*C = A
	X_End_Point = sin(angle)*Line_Size;
	
	//get Y end Point by the formula of sin(degrees)*C = B
	Y_End_Point = cos(angle)*Line_Size;
	
	//Check if X value is negative and print it the other direction
	if (X_End_Point < 0)
	{
		//Set printing direction
		X_End_Point -= X_Location;
		
		//Check if X value is negative and print it the other direction
		if (Y_End_Point < 0)
		{
			//Set Printing Direction
			Y_End_Point -= -Y_Location;
			
			//Print the Line X&Y are Negative
			myGLCD.drawLine(X_Location,Y_Location,X_End_Point,Y_End_Point);
		}
		else
		{
			//Print Line only with X changed Direction, Only X is negative
			myGLCD.drawLine(X_Location,Y_Location,X_End_Point,Y_End_Point+Y_Location);
		}
	}
	//Check if y value is negative and print it the other direction
	else if (Y_End_Point < 0)
	{
		//Set Y printing direction
		Y_End_Point -= Y_Location;
		
		//Check if X end is negative
		if (X_End_Point < 0)
		{
			//Chane X printing direction
			X_End_Point -= -X_Location;
			
			//Print the Line X&Y are Negative
			myGLCD.drawLine(X_Location,Y_Location,X_End_Point,Y_End_Point);
		}
		else
		{
			//Print Line only with Y changed Direction, Only Y is negative
			myGLCD.drawLine(X_Location,Y_Location,X_End_Point + X_Location,Y_End_Point);
		}
	}
	else
	{
		//print without ang change, X&Y are Positive
		myGLCD.drawLine(X_Location,Y_Location,X_End_Point+X_Location,Y_End_Point+Y_Location);
	}
	
}

void Line_With_angle_v2(word X_Location, word Y_Location, word Line_Size, word Line_angle)
{
	//in this function we have 4 condition X&Y positive OR X&Y negative
	//OR X=Positive Y=Negative OR X=Negative  Y=Positive, there is an if statment that fix it
	//in addition we have caculate bt tri-angle to set End point of the line.
	
	//the end of the line, the line start from X.Y Location
	word X_Start_Point,Y_Start_Point,X_End_Point, Y_End_Point;
	
	//Because i convert From Radians to degrees i use Double to keep aqurecy
	double angle = Line_angle;
	
	//The function get only RADIANS so i convert it to Degrees
	angle *= PI/180;
	
	//
	//					  ...
	//					..	.
	//                ..	.
	//              ..		.
	//            ..		.
	//       C  ..			.  B
	//        ..			.
	//      ..				.
	//    ..				.
	//  ..degrees			.
	//  .....................
	//				A
	
	if(angle<=2*PI)
	{
		angle+=PI/2;
		//get X start Point by the formula of sin(degrees)*C*0.8 = A
		X_Start_Point = X_Location-cos(angle)*Line_Size*0.8;
		
		//get Y start Point by the formula of sin(degrees)*C*0.8 = B
		Y_Start_Point = Y_Location+sin(angle)*Line_Size*0.8;
		
		//get X end Point by the formula of sin(degrees)*C = A
		X_End_Point = X_Location-cos(angle)*Line_Size;
		
		//get Y end Point by the formula of sin(degrees)*C = B
		Y_End_Point = Y_Location+sin(angle)*Line_Size;
	}
	myGLCD.drawLine(X_Start_Point,Y_Start_Point,X_End_Point,Y_End_Point);
}

void Spidometer(word X_Location,word Y_Location, unsigned char Size_Radios, unsigned char Speed_in_Precent, unsigned char Running_Speed)
{
	static unsigned char Spidometer_variable = 1;
	RePrint_Speedometer = &Spidometer_variable;
	
	if(Spidometer_variable)
	{
		for (word i = 60; i <= 300; i+=Size_Radios/10)
		{
			if (i < 110)
			{
				myGLCD.setColor(255,0,0);
				Line_With_angle_v2(X_Location,Y_Location,Size_Radios, i );
			}
			else
			{
				myGLCD.setColor(255,255,255);
				Line_With_angle_v2(X_Location,Y_Location,Size_Radios, i );
			}
			
		}
		myGLCD.setColor(0,0,0);
		
		//Make sure when the function call, it will not show up again
		Spidometer_variable = 0;
		
		//i set an external variable of Spidometer_variable in myGLCD.clrscr() so when you clear the screen
		//it will show again, the variable value in there is Spidometer_variable=1
	}
	if (Speed_in_Precent > 100)
	{
		Speed_in_Precent = 0x00;
	}
	myGLCD.setColor(0,0,0);
	Line_With_angle(X_Location,Y_Location,Size_Radios-(Size_Radios/5)-2, (100-Spidometer_Line_Cleaner)*2.5+50 );
	
	myGLCD.setColor(64,64,64);
	Line_With_angle(X_Location,Y_Location,Size_Radios-(Size_Radios/5)-2, (100-Speed_in_Precent)*2.5+50 );
	
	myGLCD.setColor(255,0,0);
	myGLCD.fillCircle(X_Location,Y_Location,Size_Radios/11);
	
	myGLCD.setColor(255,255,255);
	Spidometer_Line_Cleaner = Speed_in_Precent;
	
	if (Size_Radios > 20 && Size_Radios < 70)
	{
		Seven_Segment_Decimal_To_99(1,X_Location-13,Y_Location+Y_Location/10,Running_Speed);
	}
	else if (Size_Radios >= 70 && Size_Radios < 100)
	{
		Seven_Segment_Decimal_To_99(2,X_Location-26,Y_Location+Y_Location/8,Running_Speed);
	}
	else if (Size_Radios >= 100 && Size_Radios < 160)
	{
		Seven_Segment_Decimal_To_99(3,X_Location-45,Y_Location+Y_Location/5,Running_Speed);
	}
	
}

void Seven_Segment_Decimal_To_99(unsigned char Size_1_To_5, word X_Location, word Y_Location, char Display_Num)
{
	Main_Seven_Segment(Size_1_To_5, X_Location, Y_Location,Display_Num/10);
	switch(Size_1_To_5)
	{
		case 1:
		{
			Main_Seven_Segment(Size_1_To_5, X_Location+19, Y_Location,Display_Num%10);
			break;
		}
		case 2:
		{
			Main_Seven_Segment(Size_1_To_5, X_Location+36, Y_Location,Display_Num%10);
			break;
		}
		case 3:
		{
			Main_Seven_Segment(Size_1_To_5, X_Location+56, Y_Location,Display_Num%10);
			break;
		}
		case 4:
		{
			Main_Seven_Segment(Size_1_To_5, X_Location+90, Y_Location,Display_Num%10);
			break;
		}
		case 5:
		{
			Main_Seven_Segment(Size_1_To_5, X_Location+121, Y_Location,Display_Num%10);
			break;
		}
	}
}

void Speed_Control(word X_Location,word Y_Location, unsigned char Size_OF_X,char Max_Speed, char Present_Speed)
{
	//Y_Location of the Speed button, it need to go down according to the Max_Speed Value
	//if it is now Max_Speed = Present_Speed/2 the button should be in the meddle
	unsigned char Y_Location_Speed;
	
	//when i print on the screen it is stay there, so when the speed is changing i need to delete
	//the previous print, this global variable will remember my last speed after leaving the function
	//so i can get there and delete it
	static char Last_Speed_Value;
	
	//the filling line amount is 1/4 of the X Size, it is ratio, this variable help as to
	unsigned char Fill_Tube_Offset = Y_Location;

	//here we check that the user didn't make mistake of the present  value (because it we
	//run colors all over the screen), if he put greater value then Max_Size, we will set it to Max_Size
	if (Present_Speed > Max_Speed)
	{
		Present_Speed = Max_Speed;
	}
	
	//here we calculating the value of each speed, since the Y size of the rectangle is 3*X size
	//and the button size is X/2, so we take what left (2.5 X Size) and divide it by max speed
	Y_Location_Speed = ((Size_OF_X*2.5) / (Max_Speed));
	
	//in order to get the button current location, we multiply it by present Speed value
	Y_Location_Speed *= Present_Speed;
	
	
	//This offset is done because we don't want to ruins the up place of the rectangle, we check if it is greater
	//then 0, and if so, we cutting it by 3
	if(Y_Location_Speed)
	{
		Y_Location_Speed -= 3;
	}
	
	//this condition check if the privies speed is the same speed now, if so it will not print the same
	//thing again, this help the screen look nicer
	if ((Y_Location_Speed != Last_Speed_Value)  || Print_Speed_Control)
	{
		myGLCD.setColor(255,255,255);
		myGLCD.drawRoundRect(X_Location,Y_Location,X_Location+Size_OF_X,Y_Location+Size_OF_X*3);
		
		
		
		//Create_button((Size_OF_X-2),(Size_OF_X/2),(X_Location+1),(Y_Location+Size_OF_X*2.5-2-Y_Location_Speed),70,100,0);
		
		myGLCD.setColor(0,0,0);
		myGLCD.fillRect(X_Location+1,Y_Location+Size_OF_X*3-Last_Speed_Value-2,X_Location-1+Size_OF_X,(Y_Location+Size_OF_X*2.5-Last_Speed_Value-2));
		
		myGLCD.fillRect(X_Location+1,Y_Location+Size_OF_X*3-Last_Speed_Value-2-Size_OF_X/2,X_Location-1+Size_OF_X,(Y_Location+Size_OF_X*2.5-2));
		
		//in the loop we are printing the line according to the current speed value
		//the end condition of the loop is, current speed Y_Loacation, we filling line till that place.
		//Since Y Location relevant to the button so we take it down by dividing it ratio value
		for (unsigned char i = 0; i <= ((Size_OF_X*3/Max_Speed*Present_Speed)/(Size_OF_X/4 + Size_OF_X/8)); i++)
		{
			
			char Jump = (Size_OF_X/6*i);
			
			myGLCD.setColor(0,(255/(Size_OF_X/6)*i)+20,0);
			myGLCD.fillRoundRect(X_Location+3,Fill_Tube_Offset+Size_OF_X*3-4-Jump,X_Location+Size_OF_X-3,Fill_Tube_Offset+Size_OF_X*3-4-Size_OF_X/7-Jump);
			
			//the filling amount of the line inside of the rectangle is 1/4 of the rectangle X size, the space between
			//each line is half of the filling line amount which mean (1/4)/(1/2)= 1/8 of X_Size
			Fill_Tube_Offset -= (Size_OF_X/4)/2;
		}
		
		Create_button((Size_OF_X-2),(Size_OF_X/2),(X_Location+1),(Y_Location+Size_OF_X*2.5-2-Y_Location_Speed),70,100,0);
		Main_Seven_Segment(3,X_Location+15,Y_Location+Size_OF_X*3+8,Present_Speed);
		
		//set current speed into Last_Speed_Value1 when the next time it will enter the function it will go to the
		//previous location that the value was and delete it and then print the new value
		Last_Speed_Value = Y_Location_Speed;
		
		//Disable loop condition of printing the all thing again
		Print_Speed_Control = 0;
	}
}

void Speed_Control1(word X_Location,word Y_Location, unsigned char Size_OF_X,char Max_Speed, char Present_Speed)
{
	//Y_Location of the Speed button, it need to go down according to the Max_Speed Value
	//if it is now Max_Speed = Present_Speed/2 the button should be in the meddle
	unsigned char Y_Location_Speed;
	
	//when i print on the screen it is stay there, so when the speed is changing i need to delete
	//the previous print, this global variable will remember my last speed after leaving the function
	//so i can get there and delete it
	static char Last_Speed_Value1;
	
	//the filling line amount is 1/4 of the X Size, it is ratio, this variable help as to
	unsigned char Fill_Tube_Offset = Y_Location;

	//here we check that the user didn't make mistake of the present  value (because it we
	//run colors all over the screen), if he put greater value then Max_Size, we will set it to Max_Size
	if (Present_Speed > Max_Speed)
	{
		Present_Speed = Max_Speed;
	}
	
	//here we calculating the value of each speed, since the Y size of the rectangle is 3*X size
	//and the button size is X/2, so we take what left (2.5 X Size) and divide it by max speed
	Y_Location_Speed = ((Size_OF_X*2.5) / (Max_Speed));
	
	//in order to get the button current location, we multiply it by present Speed value
	Y_Location_Speed *= Present_Speed;
	
	
	//This offset is done because we don't want to ruins the up place of the rectangle, we check if it is greater
	//then 0, and if so, we cutting it by 3
	if(Y_Location_Speed)
	{
		Y_Location_Speed -= 3;
	}
	
	//this condition check if the privies speed is the same speed now, if so it will not print the same
	//thing again, this help the screen look nicer
	if ((Y_Location_Speed != Last_Speed_Value1)  || Print_Speed_Control1)
	{
		myGLCD.setColor(255,255,255);
		myGLCD.drawRoundRect(X_Location,Y_Location,X_Location+Size_OF_X,Y_Location+Size_OF_X*3);
		
		
		
		//Create_button((Size_OF_X-2),(Size_OF_X/2),(X_Location+1),(Y_Location+Size_OF_X*2.5-2-Y_Location_Speed),70,100,0);
		
		myGLCD.setColor(0,0,0);
		myGLCD.fillRect(X_Location+1,Y_Location+Size_OF_X*3-Last_Speed_Value1-2,X_Location-1+Size_OF_X,(Y_Location+Size_OF_X*2.5-Last_Speed_Value1-2));
		
		myGLCD.fillRect(X_Location+1,Y_Location+Size_OF_X*3-Last_Speed_Value1-2-Size_OF_X/2,X_Location-1+Size_OF_X,(Y_Location+Size_OF_X*2.5-2));
		
		//in the loop we are printing the line according to the current speed value
		//the end condition of the loop is, current speed Y_Loacation, we filling line till that place.
		//Since Y Location relevant to the button so we take it down by dividing it ratio value
		for (unsigned char i = 0; i <= ((Size_OF_X*3/Max_Speed*Present_Speed)/(Size_OF_X/4 + Size_OF_X/8)); i++)
		{
			
			char Jump = (Size_OF_X/6*i);
			
			myGLCD.setColor(0,(255/(Size_OF_X/6)*i)+20,0);
			myGLCD.fillRoundRect(X_Location+3,Fill_Tube_Offset+Size_OF_X*3-4-Jump,X_Location+Size_OF_X-3,Fill_Tube_Offset+Size_OF_X*3-4-Size_OF_X/7-Jump);
			
			//the filling amount of the line inside of the rectangle is 1/4 of the rectangle X size, the space between
			//each line is half of the filling line amount which mean (1/4)/(1/2)= 1/8 of X_Size
			Fill_Tube_Offset -= (Size_OF_X/4)/2;
		}
		
		Create_button((Size_OF_X-2),(Size_OF_X/2),(X_Location+1),(Y_Location+Size_OF_X*2.5-2-Y_Location_Speed),70,100,0);
		Main_Seven_Segment(3,X_Location+15,Y_Location+Size_OF_X*3+8,Present_Speed);
		
		//set current speed into Last_Speed_Value1 when the next time it will enter the function it will go to the
		//previous location that the value was and delete it and then print the new value
		Last_Speed_Value1 = Y_Location_Speed;
		
		//Disable loop condition of printing the all thing again
		Print_Speed_Control1 = 0;
	}
}

void RePrint_Speed_Control()
{
	Print_Speed_Control = 1;
	Print_Speed_Control1 = 1;
}

void RePrint_Spidometer()
{
	*RePrint_Speedometer = 1 ;
}

void Squre_Confirm(word X_Location, word Y_Location,  unsigned char X_Size, char V_On_Off)
{
	word X_Location_Memory = X_Location;
	myGLCD.setColor(255,255,255);
	myGLCD.drawRoundRect(X_Location,Y_Location,X_Location+X_Size,Y_Location+X_Size);
	myGLCD.setColor(232,225,225);
	myGLCD.fillRoundRect(X_Location+1,Y_Location+1,X_Location+X_Size+1,Y_Location+X_Size+1);
	
	if (V_On_Off)
	{
		myGLCD.setColor(46,192,100);
		for (char Y = 0; Y <= (X_Size*8/10);Y++)
		{
			for (char X = 0; X < X_Size/4;X++)
			{
				myGLCD.drawPixel(X_Location+X_Size/3+X,Y_Location+X_Size-X_Size/9-Y);
			}
			if (Y%2 == 0)
			{
				X_Location++;
			}
			
		}
		X_Location = X_Location_Memory;
		for (char Y = 0; Y <= (X_Size/3);Y++)
		{
			for (char X = 0; X < X_Size/4;X++)
			{
				myGLCD.drawPixel(X_Location+X_Size/3+X,Y_Location+X_Size-X_Size/9-Y);
			}
			if (Y%2 == 0)
			{
				X_Location--;
			}
			
		}
	}
}

void Print_Hebrew_String_in_EN_HE_Mode(unsigned char *Hebrew_String, word X_location, word Y_Location, unsigned char Size_String)
{
	//what this function dose, it allow you to write the word in Hebrew on the key board
	//and it translate it to the Hebrew letter, for example: g=ò  i=ï  all must be capital letters
	static word converted[100];
	//X_location = 480 - X_location;
	
	for (char i = 0; i < Size_String; i++)
	{
		switch (*Hebrew_String)
		{
			{
				case 't': converted[i] = 1;
				break;
			}
			{
				case 'c': converted[i] = 2;
				break;
			}
			{
				case 'd': converted[i] = 3;
				break;
			}
			{
				case 's': converted[i] = 4;
				break;
			}
			{
				case 'v': converted[i] = 5;
				break;
			}
			{
				case 'u': converted[i] = 6;
				break;
			}
			{
				case 'z': converted[i] = 7;
				break;
			}
			{
				case 'j': converted[i] = 8;
				break;
			}
			{
				case 'y': converted[i] = 9;
				break;
			}
			{
				case 'h': converted[i] = 10;
				break;
			}
			{
				case 'f': converted[i] = 20;
				break;
			}
			{
				case 'k': converted[i] = 30;
				break;
			}
			{
				case 'n': converted[i] = 40;
				break;
			}
			{
				case 'b': converted[i] = 50;
				break;
			}
			{
				case 'x': converted[i] = 60;
				break;
			}
			{
				case 'g': converted[i] = 70;
				break;
			}
			{
				case 'p': converted[i] = 80;
				break;
			}
			{
				case 'm': converted[i] = 90;
				break;
			}
			{
				case 'e': converted[i] = 100;
				break;
			}
			{
				case 'r': converted[i] = 200;
				break;
			}
			{
				case 'a': converted[i] = 300;
				break;
			}
			{
				case ',': converted[i] = 400;
				break;
			}
			{
				case 'l': converted[i] = 21;
				break;
			}
			{
				case 'o': converted[i] = 41;
				break;
			}
			{
				case 'i': converted[i] = 51;
				break;
			}
			{
				case ';': converted[i] = 81;
				break;
			}
			{
				case '.': converted[i] = 91;
				break;
			}
			{
				case ' ': converted[i] = 0x30;
				break;
			}
		}
		Hebrew_String++;
	}
	Print_Hebrew_String(converted,X_location,Y_Location,Size_String);
}

void scroll_Menu_Bar(word X_Location, word Y_Location,  unsigned char Size_1_OR_2,unsigned char Options_Amount, unsigned char *String, char Max_Line_Chars)
{
	
	myGLCD.setColor(255,255,255);
	myGLCD.drawRect(X_Location,Y_Location,X_Location+30*Max_Line_Chars+20,Y_Location+30);
	myGLCD.setColor(232,225,225);
	myGLCD.fillRect(X_Location+1,Y_Location+1,X_Location+30*Max_Line_Chars+20,Y_Location+30);
	
	myGLCD.setColor(0,0,0);
	Pointing_Down_Arrow(X_Location + 10, Y_Location, 20);
	
	for (char i = 0; i <= 3;i++)
	{
		myGLCD.setColor(90+i*30,90+i*30,150+i*30);
		myGLCD.drawRect(X_Location-1-i,Y_Location+31,X_Location+30*Max_Line_Chars+i+20,Y_Location+Options_Amount*25+i);
	}
	
	myGLCD.setColor(255,255,255);
	myGLCD.fillRect(X_Location,Y_Location+30,X_Location+30*Max_Line_Chars+20,Y_Location+Options_Amount*25);
	
	for (unsigned char i = 0; i < Options_Amount; i++)
	{
		myGLCD.setColor(0,0,0);
		Print_Hebrew_String_in_EN_HE_Mode(String,480-(X_Location+30*Max_Line_Chars)-10,Y_Location+8+i*25,Max_Line_Chars);
		String +=Max_Line_Chars;
	}
}

void Pointing_Down_Arrow(word X_Location, word Y_Location,  unsigned char X_Size)
{
	word X_Location_Memory = X_Location;
	for (char Y = 0; Y <= (X_Size/3);Y++)
	{
		for (char X = 0; X < X_Size/5;X++)
		{
			myGLCD.drawPixel(X_Location+X_Size/3+X,Y_Location+X_Size-X_Size/9-Y);
		}
		X_Location++;
		
	}
	
	X_Location = X_Location_Memory;
	for (char Y = 0; Y <= (X_Size/3);Y++)
	{
		for (char X = 0; X < X_Size/5;X++)
		{
			myGLCD.drawPixel(X_Location+X_Size/3+X,Y_Location+X_Size-X_Size/9-Y);
		}
		X_Location--;
	}
	
}

void Pointing_Up_Arrow(word X_Location, word Y_Location,  unsigned char X_Size)
{
	word X_Location_Memory = X_Location;
	for (char Y = 0; Y <= (X_Size/3);Y++)
	{
		for (char X = 0; X < X_Size/5;X++)
		{
			myGLCD.drawPixel(X_Location+X_Size/3+X,Y_Location+X_Size-X_Size/9-Y);
		}
		X_Location++;
		
	}
	
	X_Location = X_Location_Memory;
	for (char Y = 0; Y <= (X_Size/3);Y++)
	{
		for (char X = 0; X < X_Size/5;X++)
		{
			myGLCD.drawPixel(X_Location+X_Size/3+X,Y_Location+X_Size-X_Size/9-Y);
		}
		X_Location--;
	}
	
}

void Hebrew_Letters_Medium_Size(word Letter_Num, word X_Location,word Y_Location)
{
	//12*16
	//The letters Numbers Based on GEOMATRIA numbers
	//à=1, á=2ú â=3, ã=4, ä=5, å=5, æ=6, ç=8, è=9, é=10, ë=20, ì=30, î=40, ð=50, ñ=60, ò=70, ô=80, ö=90, ÷=100,ø=200, ù=300, ú=400
	//ê=21, í=41, ï=51, ó=81, õ=91
	//Space = 0x30;
	switch(Letter_Num)
	{
		case 1:
		{
			unsigned char _1[]{
				
				0x00, 0x00,  // ............
				0x00, 0x00,  // ............
				0x00, 0x00,  // ............
				0xC0, 0xC0,  // ##......##..
				0x60, 0xC0,  // .##.....##..
				0x30, 0xC0,  // ..##....##..
				0x19, 0xC0,  // ...##..###..
				0x7D, 0x80,  // .#####.##...
				0x6F, 0x00,  // .##.####....
				0x66, 0x00,  // .##..##.....
				0xC3, 0x00,  // ##....##....
				0xC1, 0x80,  // ##.....##...
				0xC0, 0xC0,  // ##......##..
				0xC0, 0x60,  // ##.......##.
				0x00, 0x00,  // ............
				0x00, 0x00,  // ............

			};
			Print_Letter_16_Bit(_1, X_Location, Y_Location);
			break;
		}
		case 2:
		{
			unsigned char _2[]={
				/* character 0x00E1 ('á'): [width=16, offset= 0x11B0 (4528) ] */
				
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
				0x7C, 0x00,  // .#####.....
				0x7E, 0x00,  // .######....
				0x07, 0x00,  // .....###...
				0x03, 0x00,  // ......##...
				0x03, 0x00,  // ......##...
				0x03, 0x00,  // ......##...
				0x03, 0x00,  // ......##...
				0x03, 0x00,  // ......##...
				0x03, 0x00,  // ......##...
				0x7F, 0xC0,  // .#########.
				0x7F, 0xC0,  // .#########.
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
			};
			Print_Letter_16_Bit(_2, X_Location, Y_Location);
			break;
		}
		case 3:
		{
			unsigned char _3[]={
				/* character 0x00E2 ('â'): [width=16, offset= 0x11D0 (4560) ] */
				
				0x00,  // ........
				0x00,  // ........
				0x00,  // ........
				0x78,  // .####...
				0x7C,  // .#####..
				0x0C,  // ....##..
				0x0C,  // ....##..
				0x0C,  // ....##..
				0x0C,  // ....##..
				0x3C,  // ..####..
				0x7C,  // .#####..
				0x6C,  // .##.##..
				0xC6,  // ##...##.
				0xC6,  // ##...##.
				0x00,  // ........
				0x00,  // ........
			};
			Print_Letter_8_Bit(_3, X_Location, Y_Location);
			break;
		}
		case 4:
		{
			unsigned char _4[]={
				/* character 0x00E3 ('ã'): [width=16, offset= 0x11F0 (4592) ] */
				
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
				0x7F, 0xC0,  // .#########.
				0x7F, 0xC0,  // .#########.
				0x03, 0x00,  // ......##...
				0x03, 0x00,  // ......##...
				0x03, 0x00,  // ......##...
				0x03, 0x00,  // ......##...
				0x03, 0x00,  // ......##...
				0x03, 0x00,  // ......##...
				0x03, 0x00,  // ......##...
				0x03, 0x00,  // ......##...
				0x03, 0x00,  // ......##...
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
			};
			Print_Letter_16_Bit(_4, X_Location, Y_Location);
			break;
		}
		case 5:
		{
			unsigned char _5[]={
				/* character 0x00E4 ('ä'): [width=16, offset= 0x1210 (4624) ] */
				
				0x00, 0x00,  // .............
				0x00, 0x00,  // .............
				0x00, 0x00,  // .............
				0x1F, 0xC0,  // ...#######...
				0x1F, 0xE0,  // ...########..
				0x00, 0x70,  // .........###.
				0x00, 0x30,  // ..........##.
				0x00, 0x30,  // ..........##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x00, 0x00,  // .............
				0x00, 0x00,  // .............
			};
			Print_Letter_16_Bit(_5, X_Location, Y_Location);
			break;
		}
		case 6:
		{
			unsigned char _6[]={
				
				
				0x00,  // ......
				0x00,  // ......
				0x00,  // ......
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x00,  // ......
				0x00,  // ......
			};
			Print_Letter_8_Bit(_6, X_Location, Y_Location);
			break;
		}
		case 7:
		{
			unsigned char _7[]={
				
				/* character 0x00E6 ('æ'): [width=10, offset= 0x1250 (4688) ] */
				
				0x00,  // ........
				0x00,  // ........
				0x00,  // ........
				0x7E,  // .######.
				0x7E,  // .######.
				0x18,  // ...##...
				0x30,  // ..##....
				0x30,  // ..##....
				0x30,  // ..##....
				0x30,  // ..##....
				0x30,  // ..##....
				0x30,  // ..##....
				0x30,  // ..##....
				0x30,  // ..##....
				0x00,  // ........
				0x00,  // ........
			};
			Print_Letter_8_Bit(_7, X_Location, Y_Location);
			break;
		}
		case 8:
		{
			unsigned char _8[]={
				
				/* character 0x00E7 ('ç'): [width=15, offset= 0x1270 (4720) ] */
				
				0x00, 0x00,  // .............
				0x00, 0x00,  // .............
				0x00, 0x00,  // .............
				0x1F, 0xC0,  // ...#######...
				0x1F, 0xE0,  // ...########..
				0x18, 0x70,  // ...##....###.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x00, 0x00,  // .............
				0x00, 0x00,  // .............
			};
			Print_Letter_16_Bit(_8, X_Location, Y_Location);
			break;
		}
		case 9:
		{
			unsigned char _9[]={
				
				/* character 0x00E8 ('è'): [width=14, offset= 0x1290 (4752) ] */
				
				0x00, 0x00,  // ............
				0x00, 0x00,  // ............
				0x00, 0x00,  // ............
				0x19, 0xC0,  // ...##..###..
				0x1B, 0xE0,  // ...##.#####.
				0x1A, 0x60,  // ...##.#..##.
				0x18, 0x60,  // ...##....##.
				0x18, 0x60,  // ...##....##.
				0x18, 0x60,  // ...##....##.
				0x18, 0x60,  // ...##....##.
				0x18, 0x60,  // ...##....##.
				0x1C, 0xE0,  // ...###..###.
				0x0F, 0xC0,  // ....######..
				0x07, 0x80,  // .....####...
				0x00, 0x00,  // ............
				0x00, 0x00,  // ............
			};
			Print_Letter_16_Bit(_9, X_Location, Y_Location);
			break;
		}
		case 10:
		{
			unsigned char _10[]={
				
				/* character 0x00E9 ('é'): [width=5, offset= 0x12B0 (4784) ] */
				
				0x00,  // ......
				0x00,  // ......
				0x00,  // ......
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x00,  // ......
				0x00,  // ......
				0x00,  // ......
				0x00,  // ......
				0x00,  // ......
				0x00,  // ......
				0x00,  // ......
			};
			Print_Letter_8_Bit(_10, X_Location, Y_Location);
			break;
		}
		case 20:
		{
			unsigned char _20[]={
				
				/* character 0x00EB ('ë'): [width=14, offset= 0x12E0 (4832) ] */
				
				0x00, 0x00,  // ..........
				0x00, 0x00,  // ..........
				0x00, 0x00,  // ..........
				0x7C, 0x00,  // .#####....
				0x7E, 0x00,  // .######...
				0x07, 0x00,  // .....###..
				0x03, 0x80,  // ......###.
				0x01, 0x80,  // .......##.
				0x01, 0x80,  // .......##.
				0x01, 0x80,  // .......##.
				0x03, 0x80,  // ......###.
				0x07, 0x00,  // .....###..
				0x7E, 0x00,  // .######...
				0x7C, 0x00,  // .#####....
				0x00, 0x00,  // ..........
				0x00, 0x00,  // ..........
			};
			Print_Letter_16_Bit(_20, X_Location, Y_Location);
			break;
		}
		case 30:
		{
			unsigned char _30[]={
				
				/* character 0x00EC ('ì'): [width=14, offset= 0x1300 (4864) ] */
				0x60, 0x00,  // .##.......
				0x60, 0x00,  // .##.......
				0x60, 0x00,  // .##.......
				0x7F, 0x80,  // .########.
				0x7F, 0x80,  // .########.
				0x01, 0x80,  // .......##.
				0x01, 0x80,  // .......##.
				0x03, 0x00,  // ......##..
				0x03, 0x00,  // ......##..
				0x03, 0x00,  // ......##..
				0x06, 0x00,  // .....##...
				0x06, 0x00,  // .....##...
				0x06, 0x00,  // .....##...
				0x06, 0x00,  // .....##...
				0x00, 0x00,  // ..........
				0x00, 0x00,  // ..........
			};
			Print_Letter_16_Bit(_30, X_Location, Y_Location);
			break;
		}
		case 40:
		{
			unsigned char _40[]={
				
				/* character 0x00EE ('î'): [width=15, offset= 0x1340 (4928) ] */
				0x00, 0x00,  // .............
				0x00, 0x00,  // .............
				0x00, 0x00,  // .............
				0x33, 0xC0,  // ..##..####...
				0x37, 0xE0,  // ..##.######..
				0x1E, 0x70,  // ...####..###.
				0x1C, 0x30,  // ...###....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x10, 0x30,  // ...#......##.
				0x33, 0xF0,  // ..##..######.
				0x33, 0xF0,  // ..##..######.
				0x00, 0x00,  // .............
				0x00, 0x00,  // .............
			};
			Print_Letter_16_Bit(_40, X_Location, Y_Location);
			break;
		}
		case 50:
		{
			unsigned char _50[]={
				/* character 0x00F0 ('ð'): [width=16, offset= 0x1380 (4992) ] */
				0x00,  // .......
				0x00,  // .......
				0x00,  // .......
				0x78,  // .####..
				0x7C,  // .#####.
				0x0C,  // ....##.
				0x0C,  // ....##.
				0x0C,  // ....##.
				0x0C,  // ....##.
				0x0C,  // ....##.
				0x0C,  // ....##.
				0x0C,  // ....##.
				0x7C,  // .#####.
				0x7C,  // .#####.
				0x00,  // .......
				0x00,  // .......
			};
			Print_Letter_8_Bit(_50, X_Location, Y_Location);
			break;
		}
		case 60:
		{
			unsigned char _60[]={
				/* character 0x00F1 ('ñ'): [width=16, offset= 0x13A0 (5024) ] */
				0x00, 0x00,  // ............
				0x00, 0x00,  // ............
				0x00, 0x00,  // ............
				0x0F, 0x00,  // ....####....
				0x3F, 0xC0,  // ..########..
				0x30, 0xC0,  // ..##....##..
				0x60, 0x60,  // .##......##.
				0x60, 0x60,  // .##......##.
				0x60, 0x60,  // .##......##.
				0x60, 0x60,  // .##......##.
				0x60, 0x60,  // .##......##.
				0x30, 0xC0,  // ..##....##..
				0x3F, 0xC0,  // ..########..
				0x0F, 0x00,  // ....####....
				0x00, 0x00,  // ............
				0x00, 0x00,  // ............
			};
			Print_Letter_16_Bit(_60, X_Location, Y_Location);
			break;
		}
		case 70:
		{
			unsigned char _70[]={
				/* character 0x00F2 ('ò'): [width=15, offset= 0x13C0 (5056) ] */
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
				0x30, 0xC0,  // ..##....##.
				0x30, 0xC0,  // ..##....##.
				0x30, 0xC0,  // ..##....##.
				0x18, 0xC0,  // ...##...##.
				0x18, 0xC0,  // ...##...##.
				0x18, 0xC0,  // ...##...##.
				0x18, 0xC0,  // ...##...##.
				0x19, 0x80,  // ...##..##..
				0x1B, 0x80,  // ...##.###..
				0x1F, 0x00,  // ...#####...
				0x7C, 0x00,  // .#####.....
				0x60, 0x00,  // .##........
				0x00, 0x00,  // ...........
			};
			Print_Letter_16_Bit(_70, X_Location, Y_Location);
			break;
		}
		case 80:
		{
			unsigned char _80[]={
				/* character 0x00F4 ('ô'): [width=14, offset= 0x1400 (5120) ] */
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
				0x3E, 0x00,  // ..#####....
				0x7F, 0x80,  // .########..
				0x61, 0x80,  // .##....##..
				0x60, 0xC0,  // .##.....##.
				0x78, 0xC0,  // .####...##.
				0x38, 0xC0,  // ..###...##.
				0x00, 0xC0,  // ........##.
				0x01, 0xC0,  // .......###.
				0x43, 0x80,  // .#....###..
				0x7F, 0x00,  // .#######...
				0x3E, 0x00,  // ..#####....
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
			};
			Print_Letter_16_Bit(_80, X_Location, Y_Location);
			break;
		}
		case 90:
		{
			unsigned char _90[]={
				/* character 0x00F6 ('ö'): [width=15, offset= 0x1440 (5184) ] */
				0x00, 0x00,  // ..........
				0x00, 0x00,  // ..........
				0x00, 0x00,  // ..........
				0xC1, 0x80,  // ##.....##.
				0x61, 0x80,  // .##....##.
				0x31, 0x80,  // ..##...##.
				0x31, 0x80,  // ..##...##.
				0x1B, 0x00,  // ...##.##..
				0x0E, 0x00,  // ....###...
				0x04, 0x00,  // .....#....
				0x06, 0x00,  // .....##...
				0x03, 0x00,  // ......##..
				0xFF, 0x80,  // #########.
				0xFF, 0x80,  // #########.
				0x00, 0x00,  // ..........
				0x00, 0x00,  // ..........
			};
			Print_Letter_16_Bit(_90, X_Location, Y_Location);
			break;
		}
		case 100:
		{
			unsigned char _100[]={
				/* character 0x00F7 ('÷'): [width=15, offset= 0x1460 (5216) ] */
				0x00, 0x00,  // ............
				0x00, 0x00,  // ............
				0x00, 0x00,  // ............
				0x3F, 0xE0,  // ..#########.
				0x3F, 0xE0,  // ..#########.
				0x00, 0x60,  // .........##.
				0x00, 0x60,  // .........##.
				0x30, 0xC0,  // ..##....##..
				0x30, 0xC0,  // ..##....##..
				0x31, 0x80,  // ..##...##...
				0x31, 0x80,  // ..##...##...
				0x31, 0x80,  // ..##...##...
				0x30, 0x00,  // ..##........
				0x30, 0x00,  // ..##........
				0x30, 0x00,  // ..##........
				0x00, 0x00,  // ............
			};
			Print_Letter_16_Bit(_100, X_Location, Y_Location);
			break;
		}
		case 200:
		{
			unsigned char _200[]={
				/* character 0x00F8 ('ø'): [width=16, offset= 0x1480 (5248) ] */
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
				0x7E, 0x00,  // .######....
				0x7F, 0x80,  // .########..
				0x03, 0x80,  // ......###..
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
			};
			Print_Letter_16_Bit(_200, X_Location, Y_Location);
			break;
		}
		case 300:
		{
			unsigned char _300[]={
				/* character 0x00F9 ('ù'): [width=14, offset= 0x14A0 (5280) ] */
				0x00, 0x00,  // ...............
				0x00, 0x00,  // ...............
				0x00, 0x00,  // ...............
				0x61, 0x8C,  // .##....##...##.
				0x61, 0x8C,  // .##....##...##.
				0x61, 0x8C,  // .##....##...##.
				0x61, 0x8C,  // .##....##...##.
				0x63, 0x0C,  // .##...##....##.
				0x7F, 0x18,  // .#######...##..
				0x30, 0x18,  // ..##.......##..
				0x30, 0x18,  // ..##.......##..
				0x38, 0x70,  // ..###....###...
				0x1F, 0xF0,  // ...#########...
				0x07, 0xC0,  // .....#####.....
				0x00, 0x00,  // ...............
				0x00, 0x00,  // ...............
			};
			Print_Letter_16_Bit(_300, X_Location, Y_Location);
			break;
		}
		case 400:
		{
			unsigned char _400[]={
				/* character 0x00FA ('ú'): [width=16, offset= 0x14C0 (5312) ] */
				0x00, 0x00,  // ..............
				0x00, 0x00,  // ..............
				0x00, 0x00,  // ..............
				0x3F, 0xE0,  // ..#########...
				0x3F, 0xF0,  // ..##########..
				0x06, 0x38,  // .....##...###.
				0x06, 0x18,  // .....##....##.
				0x06, 0x18,  // .....##....##.
				0x06, 0x18,  // .....##....##.
				0x06, 0x18,  // .....##....##.
				0x06, 0x18,  // .....##....##.
				0x06, 0x18,  // .....##....##.
				0x3E, 0x18,  // ..#####....##.
				0x3C, 0x18,  // ..####.....##.
				0x00, 0x00,  // ..............
				0x00, 0x00,  // ..............
			};
			Print_Letter_16_Bit(_400, X_Location, Y_Location);
			break;
		}
		case 21:
		{
			unsigned char _21[]={
				
				/* character 0x00EA ('ê'): [width=14, offset= 0x12C0 (4800) ] */
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
				0x00, 0x00,  // ...........
				0x7E, 0x00,  // .######....
				0x7F, 0x80,  // .########..
				0x03, 0x80,  // ......###..
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
				0x00, 0xC0,  // ........##.
			};
			Print_Letter_16_Bit(_21, X_Location, Y_Location);
			break;
		}
		case 41:
		{
			unsigned char _41[]={
				/* character 0x00ED ('í'): [width=15, offset= 0x1320 (4896) ] */
				0x00, 0x00,  // .............
				0x00, 0x00,  // .............
				0x00, 0x00,  // .............
				0x1F, 0xC0,  // ...#######...
				0x1F, 0xE0,  // ...########..
				0x18, 0x70,  // ...##....###.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x18, 0x30,  // ...##.....##.
				0x1F, 0xF0,  // ...#########.
				0x1F, 0xF0,  // ...#########.
				0x00, 0x00,  // .............
				0x00, 0x00,  // .............
			};
			Print_Letter_16_Bit(_41, X_Location, Y_Location);
			break;
		}
		case 51:
		{
			unsigned char _51[]={
				/* character 0x00EF ('ï'): [width=10, offset= 0x1360 (4960) ] */
				0x00,  // ......
				0x00,  // ......
				0x00,  // ......
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				0x18,  // ...##.
				
			};
			Print_Letter_8_Bit(_51, X_Location, Y_Location);
			break;
		}
		case 81:
		{
			unsigned char _81[]={
				/* character 0x00F3 ('ó'): [width=16, offset= 0x13E0 (5088) ] */
				0x00, 0x00,  // ............
				0x00, 0x00,  // ............
				0x00, 0x00,  // ............
				0x3E, 0x00,  // ..#####.....
				0x7F, 0x80,  // .########...
				0x61, 0xC0,  // .##....###..
				0x60, 0xC0,  // .##.....##..
				0x60, 0xC0,  // .##.....##..
				0x78, 0xC0,  // .####...##..
				0x38, 0xC0,  // ..###...##..
				0x00, 0xC0,  // ........##..
				0x00, 0xC0,  // ........##..
				0x00, 0xC0,  // ........##..
				0x00, 0xC0,  // ........##..
				0x00, 0xC0,  // ........##..
				0x00, 0xC0,  // ........##..
			};
			Print_Letter_16_Bit(_81, X_Location, Y_Location);
			break;
		}
		case 91:
		{
			unsigned char _91[]={
				/* character 0x00F5 ('õ'): [width=15, offset= 0x1420 (5152) ] */
				0x00, 0x00,  // ..........
				0x00, 0x00,  // ..........
				0x00, 0x00,  // ..........
				0xC1, 0x80,  // ##.....##.
				0xE1, 0x80,  // ###....##.
				0x61, 0x80,  // .##....##.
				0x73, 0x80,  // .###..###.
				0x37, 0x00,  // ..##.###..
				0x3E, 0x00,  // ..#####...
				0x1C, 0x00,  // ...###....
				0x18, 0x00,  // ...##.....
				0x18, 0x00,  // ...##.....
				0x18, 0x00,  // ...##.....
				0x18, 0x00,  // ...##.....
				0x18, 0x00,  // ...##.....
				0x18, 0x00,  // ...##.....
			};
			Print_Letter_16_Bit(_91, X_Location, Y_Location);
			break;
		}
		case 0x30:
		{
			unsigned char _0x30[]={
				
				/* character 0x00E9 (' '): [width=5, offset= 0x12B0 (4784) ] */
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
				0x00, 0x00, // ................
			};
			Print_Letter_16_Bit(_0x30, X_Location, Y_Location);
			break;
		}
	}
}

void Print_Letter_8_Bit(unsigned char *Bit_value,word X,word Y)
{

	for (char i = 0; i < 16; i++)
	{
		for (char bit_1_OR_0 = 0; bit_1_OR_0 <= 7; bit_1_OR_0++)
		{
			if (Bit_value[i] & (1 << bit_1_OR_0))
			{
				myGLCD.drawPixel(X-(bit_1_OR_0),Y+i);
			}
		}
		
	}
}

void Set_Font_Size(char Size)
{
	if (Size == Medium)
	{
		*Font_Size = 2;
	}
	else if (Size == Big)
	{
		*Font_Size = 3;
	}
	else if (Size == Small)
	{
		*Font_Size = 1;
	}
	
}

