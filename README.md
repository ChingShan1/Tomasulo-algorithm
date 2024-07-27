Tomasulo算法是一種動態調度技術，用於提高CPU執行效率，解決指令級並行性中的依賴問題。

主要以三個不同的function去處理，分別為issue, Execute, WriteResult

issue: 主要功能是判斷目前這個指令能不能被讀取或執行

Execute: 如果執行條件都被滿足，就去執行，反則返回給buffer

WriteResult: 把正確的結果寫回buffer，順便廣播這個處理的暫存器目前沒人使用

執行結果畫面:
輸入: test5.txt, 一段組成語言程式碼

![test5](https://github.com/user-attachments/assets/50428c54-57f0-450b-8522-af671e5a54c8)

輸出:
紅色框框: 指令中不同的register被執行所需要等待cycle的時間。
綠色框框: 目前register和buffer的狀態，0表示在沒人使用，1表示現在使用中。

![圖片1](https://github.com/user-attachments/assets/14f81cda-e17e-4e82-b7c6-611a306b52ca)



