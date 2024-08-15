- Q1:請大致解釋 make install做了甚麼事情。

第三方 open source project 安裝。

- Q2:makefile是如何協助編譯這份project的?(從inc/ src/回答)

識別 file dependency ，只需重新 compile 更動過的 file。


- Q3:請解釋在Step3中如何設計bit field演算法，如何決定要使用多少bit，這樣做有甚麼優點?



Q4:在Step4中，你如何處理邊界問題?(若大圖的長寬不是小圖的倍數，你會怎麼處理?)
Q5:在Step4中，如果每張小圖的大小都不一樣，你會怎麼處理?
Q6:使用valgrind及cppcheck來對你的程式做動態分析與靜態分析，並秀出執行結果與報告。並解釋這兩種分析有何不同?(try to install cppcheck by your self...)