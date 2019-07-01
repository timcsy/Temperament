平均律合成器 (Temperament Synthesiser)
===

Github: https://github.com/timcsy/Temperament
[English Version](../README.md)

你有曾經想過為何八度音中間是12個半音嗎？它可以是其他數字嗎？這個外掛可以讓你探索不同平均律的世界，也可以藉由連分數的計算來得到一組好聽的平均律。

此外，有許多民族音樂並非12平均律，所以你可以用這個好用的工具來彈奏不同文化的音樂。（例如：中國的五聲音階）

如果你想要知道如何計算平均率、為何12平均率很好、以及連分數與平均律之間的關係，你可以參考以下資料：

1. [音階裡的數學（一）：音階裡的生成元 (PDF)](http://mathcenter.ck.tp.edu.tw/Resources/Ctrl/ePaper/ePaperOpenFileX.ashx?autoKey=1007)
2. [音階裡的數學（二）：一個八度內應該有幾個音？ (PDF)](http://mathcenter.ck.tp.edu.tw/Resources/Ctrl/ePaper/ePaperOpenFileX.ashx?autoKey=1008)
3. [從鋼琴調音談數學與音樂](http://web.math.sinica.edu.tw/math_media/d331/33102.pdf)
4. [丟番圖逼近](https://zh.wikipedia.org/wiki/丟番圖逼近)
5. [連分數](https://zh.wikipedia.org/wiki/連分數)

![](images/Temperament.png)

使用說明
---
將AU或VST3的外掛（位於 plugins/ 資料夾）放到適當的位置（視編曲軟體不同而有不同的安裝位置）

參數說明:
- Center Note: 中央基準音符（預設值是 A4=69，你也可以用 C4=60）。
- Center Frequency: 中央基準音符的頻率（預設值是 A4=440Hz，你也可以用 C4=261.626，或是參考這個網站：http://www.inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies）。
- Overtune1&2: 兩個不同的泛音，產生出來的平均律在這兩泛音的音程聽起來最接近和諧。
- Precision: 用連分數計算填充音符數目時所使用的精度T。
- Temperament: 你想要在兩個泛音構成的音程中所切的等分。它可以自動被計算（如果改變泛音或是精度），也可以手動設置。

開發
---
環境需求: JUCE

原始碼位於 Source/ 資料夾。
首先，建立一個 JUCE 的 Audio Plugin with JUCE 專案，然後
1. Plugin Formats 中勾選 "VST3" 及 "AU"
2. Plugin Characteristics 中勾選 "Plugin is a Synth" 及 "Plugin MIDI Input"

如果對於 JUCE 有任何疑問，可以參考官網：https://juce.com/，或是看我整理的筆記：https://hackmd.io/@timcsy/JUCE

之後，打開IDE開始進行編輯，享受吧！

授權條款(MIT)
---
Copyright (C) 2019 張頌宇

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.