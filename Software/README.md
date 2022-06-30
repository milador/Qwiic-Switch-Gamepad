# Software

## Software requirements  

### Software or Libraries to Download

  1. [Arduino IDE](https://www.arduino.cc/en/software)
  2. [Main Code](./Code/)
  3. [SparkFun_Qwiic_GPIO Library](https://github.com/sparkfun/SparkFun_Qwiic_GPIO_Library)
  4. [Adafruit_NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)


## Software Setup Process

### Debuggers and Compilers Setup Process

  1. Download the [Arduino IDE](https://www.arduino.cc/en/software) executable installation file suitable for your OS.
  2. Double click on the executable file to Install the **Arduino IDE**.
  3. Open and start the **Arduino IDE**.
  4. Go to **File > Preferences**.
  5. Add following link as a new line under **Additional Board Manager URLs** : https://www.adafruit.com/package_adafruit_index.json
  6. Restart the **Arduino IDE**
  7. Open the **Boards Manager** option from the **Tools > Board** menu and install **Adafruit SAMD Boards by Adafruit**
  8. Wait until the IDE finishes installing the cross-compiling toolchain and tools associated with Board Support Package. This may take few minutes.
  9. That’s it! The installation of **Arduino IDE** and the Board Support Packages is completed.

### Main Code Setup Process

  1. Visit the **SparkFun_Qwiic_GPIO** library github repository page.
  2. Click on **Code > Download Zip** to download **SparkFun_Qwiic_GPIO_Library**.
  3. Extract **SparkFun_Qwiic_GPIO_Library-master.zip** file
  4. Rename **SparkFun_Qwiic_GPIO_Library-master** folder to **SparkFun_Qwiic_GPIO_Library** folder under **SparkFun_Qwiic_GPIO_Library-master** subdirectory. 
  5. Copy or move **SparkFun_Qwiic_GPIO_Library** folder to Arduino installation library subdirectory. As an example: This is found under **C:\Program Files (x86)\Arduino\libraries in windows 10**.
  6. Visit the **Qwiic_Switch_Gamepad_Software.ino** raw source code file under Code directory.
  7. Right click on the source code or any place on this page and select **Save Page As…**
  8. Select the directory you would like to save the software in your computer. 
  9. Change File name from **Qwiic_Switch_Gamepad_Software** to **Qwiic_Switch_Gamepad_Software.ino**
  10. Change **Save as type** to **All Files**.
  11. Click on **Save** button.
  12. Visit the **TinyUSB_Gamepad.h** raw source code file under Code directory.
  13. Right click on the source code or any place on this page and select **Save Page As…**
  14. Select the directory you selected in step 8.
  15. Click on **Save** button.
  16. Open the directory you selected in step 8.
  17. Double left click or open **Qwiic_Switch_Gamepad_Software** file
  18. **Arduino IDE** will ask your permission to create a new sketch folder named **Qwiic_Switch_Gamepad_Software** and move **Qwiic_Switch_Gamepad_Software.ino** under this folder.
  19. Click on the **Ok** button. 
  20. **Arduino IDE** should now open the **Qwiic_Switch_Gamepad_Software.ino** file automatically.
  21. Select the Board under **Tools > Board > Adafruit SAMD Boards** as **Adafruit QT PY (SAMD21)**
  22. Select the correct USB Stack under **Tools > USB Stack** as **TinyUSB** 
  23. Select the correct port number under **Tools > Port** which should show COM XX (Adafruit QT PY) 
  24. Press the **Verify** button to make sure there is no problem with the software and libraries. 
  25. Press **Upload** button 


