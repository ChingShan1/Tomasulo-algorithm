Tomasulo算法是一種動態調度技術，用於提高CPU執行效率，解決指令級並行性中的依賴問題。

主要以三個不同的function去處理，分別為issue, Execute, WriteResult

issue: 主要功能是判斷目前這個指令能不能被讀取或執行

Execute: 如果執行條件都被滿足，就去執行，反則返回給buffer

WriteResult: 把正確的結果寫回buffer，順便廣播這個處理的暫存器目前沒人使用

執行結果畫面:  
![tom_1](https://github.com/ChingShan1/Tomasulo-algorithm/assets/34879924/69a61557-9e46-4023-9dfc-0427dd3fab3a)  
