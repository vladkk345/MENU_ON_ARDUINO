// Подключение библиотек
#include <GyverOLED.h> 
#include <GyverButton.h>

#define ITEMS 16 // Количество пунктов в меню

GButton down(4, HIGH_PULL, NORM_OPEN); // Кнопка вниз
GButton up(5, HIGH_PULL, NORM_OPEN); // Кнопка вверх
GButton ok(6, HIGH_PULL, NORM_OPEN); // Кнопка OK

GyverOLED<SSD1306_128x64, OLED_BUFFER> oled; // Создание объекта с именем oled

uint8_t data[ITEMS]; // Объявление массива, содержащий данные по 16 пунктам меню
bool flag = true; // Флаг смены состояния

// Инициализация и настройка параметров дисплея
void setup() {
  delay(50);
  oled.init();
  oled.setContrast(255); 
}

void loop(void) { 
  static uint8_t pointer = 0; // Объявление указателя 
  // Объявление отображаемых строк на дисплее
  String str_one = "Parameter."; 
  String str_two = ":";

  // Обработка нажатия кнопок
  down.tick();
  up.tick();
  ok.tick();

  if(down.isClick() or down.isHold()) // Если кнопка вниз нажата или удержана
  {
      if(flag) // Если флаг установлен, то переместить указатель на 1 позицию вниз
      {
          pointer = constrain(pointer + 1, 0, ITEMS - 1); // ограничение по пунктам меню (до 16 пунктов)
      }
      else // В противном случае увеличить счетчик данных
      {  
        data[pointer]++;      
      }   
  }

  if(up.isClick() or up.isHold()) // Если кнопка вверх нажата или удержана
  {
     if(flag) // Если флаг установлен, то переместить указатель на 1 позицию вверх
     {
         pointer = constrain(pointer - 1, 0, ITEMS - 1); // ограничение по пунктам меню (до 16 пунктов)
     }
     else // В противном случае уменьшить счетчик данных
     {      
        data[pointer]--;              
     }
  }
  
  if(ok.isClick()) // Если нажата кнопка ОК
  {
     flag = !flag;  // Инвертировать состояние флага
  }
  
  oled.clear(); // Очистить дисплей
  oled.home(); // Вернуться в начало дисплея
  
  if(pointer < 8) // Если указатель меньше 8
  { 
    // Цикл для отображения первых 8 пунктов меню
     for(uint8_t i = 0; i < 8;i++) 
     {
       oled.setCursor(8,i); // Установка курсора на начало строк
       oled.println(str_one + i + str_two); // Отображение строк (названий пунктов меню) с номерами
       oled.setCursor(85,i); // Установка курсора на конец строк
       oled.print(data[i]); // Вывод данных 
     } 
  }
  
  if(pointer >= 8) // Если указатель больше 8
  {
    // Цикл для отображения остальных 8 пунктов меню
     for(uint8_t i = 0; i < 8;i++)
     {
       oled.setCursor(8,i); // Установка курсора на начало строк
       oled.println(str_one + (i+8) + str_two); // Отображение строк (названий пунктов меню) с номерами
       oled.setCursor(85,i); // Установка курсора на конец строк
       oled.print(data[i+8]); // Вывод данных
     } 
  } 
  PrintPointer(pointer); // Вызов функции вывода указателя
  oled.update(); // Обновить дисплей
}

// ФункциЯ вывода указателя
void PrintPointer(uint8_t ptr)
{
    if(ptr >= 8) // Если указатель больше 8
    {
      if(flag) // Если флаг установлен
      {
        oled.setCursor(0, ptr-8); // Установка курсора на позицию 0 и (номер указателя - 8)
        oled.print(">"); // Вывод значка указателя
      }
      else // В противном случае
      {
        oled.setCursor(120, ptr-8); // Установка курсора на позицию 120 и (номер указателя - 8)
        oled.print("<"); // Вывод значка указателя
      }
    } 
    else // В противном случае
    {
      if(flag) // Если флаг по-прежнему установлен
      {
        oled.setCursor(0, ptr); // Установка курсора на позицию 0 и (номер указателя)
        oled.print(">"); // Вывод значка указателя
      }
      else
      {
        oled.setCursor(120, ptr); // Установка курсора на позицию 120 и (номер указателя)
        oled.print("<"); // Вывод значка указателя
      }
    }
}
