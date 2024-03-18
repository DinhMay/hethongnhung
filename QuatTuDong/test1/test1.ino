int button = 10;              // nút nhấn được kết nối với pin 5

    int led1 = 13;

    int led2 = 11;

    int val;                         // đọc trạng thái pin
    int val2;                       // đọc trạng thái bị trì hoãn
    int buttonState;           // giữ trạng thái nút
    int Mode = 0;              // led sẽ sáng ở chế độ nào

void setup () 
{
      pinMode(button, INPUT);    // đặt nút nhấn làm ngỏ vào
      pinMode(led1, OUTPUT);
      pinMode(led2, OUTPUT);
      buttonState = digitalRead(button);   // đọc trạng thái ban đầu
}

void loop ()
{
      val = digitalRead(button);      // đọc giá trị đầu vào và lưu trữ nó trong val
      delay(10);                         // 10 mili giây là thời gian chờ
      val2 = digitalRead(button);     // đọc lại đầu vào để kiểm tra xem có bị trả lại không
      if (val == val2) // make sure we got 2 consistant readings!
        {                 
        if (val != buttonState) // trạng thái nút đã thay đổi!
            {          
             if (val == LOW)// kiểm tra xem nút có được nhấn hay không
             {                
                     if (Mode == 0) 
                      {          
                       Mode = 1;               
                      }
               else 
               {
                     if (Mode == 1) 
                      {        
                       Mode = 2;           
                      } 
               else 
               {
                    if (Mode == 2) 
                      {      
                       Mode = 3;           
                      } 
               else 
                {
                    if (Mode == 3) 
                      { 
                       Mode = 0;          
                      }
                }
                }
                }
               }
           }
        buttonState = val;                // lưu trạng thái mới trong biến của chúng tôi
      }

      //Thiết lập các chế độ
      if (Mode == 0) 
        {                           
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
        }

      if (Mode == 1) 
        { 
          digitalWrite(led1, HIGH);
          digitalWrite(led2, LOW);
        }

      if (Mode == 2) 
        { 
          digitalWrite(led1, LOW);
          digitalWrite(led2, HIGH);
        }
      if (Mode == 3)  
        { 
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
        }    
}