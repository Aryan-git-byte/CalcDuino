14/07:

i srarted by opening the tinkercad since my net was bit slow it took few mins to open, then i dropped keypad and arduino uno on my design and started tinkering around. i even played with block coding in the website after that i was confused between arduino backpack and liquid crystal since both description said almost same thing that it works with liquid crystal. i got adafruit liquid crystal started readings its docs and experimented. then read keypad docs and started tinkering. till the EOD i had figured out on how to parse keypad inputs to lcd.

15/07:
i started by opening tinkercad and yesterday i had a chat with tanuki to add smthg different to my calculator so i added a buzzer and a ir sensor to control it wirelessly. i first read its doc and example code tinkercad had given but instead i started redesigning hardware since itwasnt neat last time, but now it is:

![image](/api/uploads/project-screenshots/68yirTN6lRhzq7ClnOLf1yXNKK0qz5dk/external/8ca4827a-3a87-4ab5-888b-9a297bb03c01.webp)
then i started reading the docs of ir sensor again, and implementing it in my code and for sm reason adafruit liquidcrystal libray and ir remote library didnt compiled together in tinkercad  although it did in my ide, so i shifted to liquid crystal instead.
then after that one by one i started adding functions in code. 
step by step, like first adding parsing numbers from both ir sensor and keypad to the arduino, then standardizing the input instead of separate, then making function to decode ir remote, then first number, then operators, clear, second number, equal too and all, and then it was complete. now i came back to tinkercad to compile it for final time and wtf?, it said invalid header file, so i switched to wokwi yeahh.
redrew hardware :

![image](/api/uploads/project-screenshots/68yirTN6lRhzq7ClnOLf1yXNKK0qz5dk/external/61890a1a-f42c-4b19-afd2-96d0b2a7ecbf.webp)
 
i also tried platformio instead of arduino, but nah arduino is best. i wrote needed files and simulated it. and my lcd address and ir decoder had issues. so i fixed that. simulated , had fun, completed firmware. wrote readme, published, now writing journal published.
