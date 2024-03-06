#include <TV_16F887.c>
#include <tv_lcd.c>

#define s1 pin_a0
#define s2 pin_a1
#define s3 pin_a2
#define s4 pin_a3
#define s5 pin_a4

#define enA pin_c1 // ccp2
#define enB pin_c2 // ccp1
#define in1 pin_c0
#define in2 pin_c3
#define in3 pin_c4
#define in4 pin_c5 

#define trigger pin_b1
#define echo    pin_b0

#define A_speed 600
#define B_speed 600

void left();
void right();
void forward();
void stop();
void sensors();
void lcd_display(int8 state);

void avoid_obs();
int16 get_distance();

int1 i1, i2, i3, i4, i5;
int8 state;
int8 set_distance = 15;
int16 i, distance = 0;

void main()
{  	
   set_tris_c (0x00);
   set_tris_a (0xff);
   set_tris_d(0x00); // for display lcd
   set_tris_e(0x00); // rs, rw,... of lcd
   set_tris_b(0x01); // for trig, echo
   
   setup_timer_1(t1_internal | t1_div_by_1); // dem thoi gian trig
   
   setup_ccp1(ccp_pwm);
   setup_ccp2(ccp_pwm);
   setup_timer_2(t2_div_by_16, 249, 1);
   set_pwm1_duty(A_speed);
   set_pwm2_duty(B_speed);
 
   output_high(enA);
   output_high(enB);
	stop();
	delay_ms(2000);
  	
   lcd_setup();

   while(1)
   {
   	sensors();
   	//avoid_obs();
   }
}

void left()
{
	output_low(in1);
	output_low(in2);

	output_low(in3);
	output_high(in4);
  	
	lcd_display(3);
}

void right()
{
	output_low(in1);
	output_high(in2);
  	
	output_low(in3);
	output_low(in4);
	
	lcd_display(4);
}

void forward()
{
	output_low(in1);
	output_high(in2);

	output_low(in3);
	output_high(in4);
  	
	lcd_display(1);
}

void stop()
{
	output_high(in1);
	output_high(in2);
  	
	output_high(in3);
	output_high(in4);
  	
	lcd_display(2);
}

void backward()
{
	output_high(in1);
	output_low(in2);
  	
	output_high(in3);
	output_low(in4);
  	
	lcd_display(5);
}

void sensors()
{
   i1 = input(s1);
   i2 = input(s2);
   i3 = input(s3);
   i4 = input(s4);
   i5 = input(s5);
   
	if(i1 == 1 && i2 == 1 && i3 == 0 && i4 == 1 && i5 == 1)
	{
   	forward();
	}

	else if(i1 == 1 && i2 == 0 && i3 ==  0 && i4 == 1 && i5 == 1)
	{
   	left();
	}

	else if(i1 == 0 && i2 == 0 && i3 == 0 && i4 == 1 && i5 == 1)
	{
   	left();
	}

	else if(i1 == 0 && i2 == 1 && i3 == 0 && i4 == 1 && i5 == 1)
	{
   	left();
	}

	else if(i1 == 0 && i2 == 0 && i3 == 1 && i4 ==1 && i5 ==1)
	{
   	left();
	}

	else if(i1 == 1 && i2 == 1 && i3 == 0 && i4 == 0 && i5 == 1)
	{
   	right();
	}

	else if(i1 ==  1 && i2 == 1 && i3 == 0 && i4 == 0 && i5 == 0)
	{
   	right();
	}
  	
	else if(i1 == 1 && i2 == 1 && i3 == 0 && i4 == 1 && i5 == 0)
	{
   	right();
	}

	else if(i1 ==1 && i2 == 1 && i3 == 1 && i4 == 0 && i5 == 0)
	{
   	right();
	}

	else if(i1 == 1 && i2 == 0 && i3 == 1 && i4 == 1 && i5 == 1)
	{
   	left();
	}

	else if(i1 == 1 && i2 == 1 && i3 == 1 && i4 == 0 && i5 == 1)
	{
   	right();
	}

	else if(i1 == 0 && i2 == 0 && i3 == 0 && i4 == 0 && i5 == 1)
	{
   	left();
	}
  	
	else if( i1 == 1 && i2 == 0 && i3 == 0 && i4 == 0 && i5 == 0)
	{
   	right();
	}

	else if( i1 == 0 && i2 == 1 && i3 == 1 && i4 == 1 && i5 == 1)
	{
   	left();
	}

	else if(i1 == 1 && i2 == 1 && i3 == 1 && i4 == 1 && i5 == 0)
	{
   	right();
	}

	else if(i1 == 0 && i2 == 1 && i3 == 1 && i4 == 0 && i5 == 0)
	{
   	right();
	}

	else if(i1 == 0 && i2 == 1 && i3 == 1 && i4 == 0 && i5 == 1)
	{
   	right();
	}

	else if(i1 == 1 && i2 == 0 && i3 == 0 && i4 == 0 && i5 == 1)
	{
   	left();
	}

	else
	{
   	stop();
	}
}

void lcd_display(int8 state)
{
	lcd_command(addr_line1);
	lcd_data("State: ");
	lcd_command(addr_line1 + 6);
	switch(state)
	{
		case 1: 
			lcd_data(" Forward  ");
			break;
		case 2: 
			lcd_data(" Stop     ");
			break;
		case 3: 
			lcd_data(" Left     ");
			break;
		case 4: 
			lcd_data(" Right    ");
			break;
		case 5:
			lcd_data(" Backward ");
			break;
		case 6:
			lcd_data(" Avoid    ");
			break;
	}
	lcd_command(addr_line2);
	lcd_data("Distance: ");
	lcd_command(addr_line2 + 10);
	lcd_data(distance);
	lcd_data(" cm ");
}

void avoid_obs()
{ 	
  	
	output_high(trigger);
	delay_us(10);
	output_low(trigger);
  	
	while(input(echo) != 1);
	set_timer1(0);
	while(input(echo) != 0);
	i = get_timer1();
	distance = i * 0.017;

	if(distance < set_distance)
	{
		stop();
		delay_ms(300);
	  	
		backward();
		delay_ms(300);
		stop();
		delay_ms(100);
	  	
		left();
		delay_ms(300);
		stop();
		delay_ms(100);
	  	
		forward();
		delay_ms(500);
		stop();
		delay_ms(100);
	  	
		right();
		delay_ms(500);
		stop();
		delay_ms(100);
	  	
		forward();
		delay_ms(550);
		stop();
		delay_ms(100);
	  	
		right();
		delay_ms(400);
		stop();
		delay_ms(100);
	  	
		forward();
	  	
		while(i3 == 1)
		{
			i1 = input(s1);
   		i2 = input(s2);
   		i3 = input(s3);
   		i4 = input(s4);
   		i5 = input(s5);
		}
		lcd_display(6);
	}
}
