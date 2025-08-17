# First Level Heading

Paragraph.

## Second Level Heading

Paragraph.

- bullet
+ other bullet
* another bullet
    * child bullet

1. ordered
2. next ordered

### Third Level Heading

Some *italic* and **bold** text and `inline code`.

An empty line starts a new paragraph.

Use two spaces at the end  
to force a line break.

A horizontal ruler follows:

---

Add links inline like [this link to the Qt homepage](https://www.qt.io),
or with a reference like [this other link to the Qt homepage][1].

    Add code blocks with
    four spaces at the front.

> A blockquote
> starts with >
>
> and has the same paragraph rules as normal text.

First Level Heading in Alternate Style
======================================

Paragraph.

Second Level Heading in Alternate Style
---------------------------------------

Paragraph.

[1]: https://www.qt.io

# 基于Qt的音乐播放器项目开发记录
## 日期：2025-8-15
### 完成的工作：
1. 实现了歌词显示功能，通过点击按钮控制歌词的显示与隐藏，同时设置了歌词的样式表格式。
2. 简单的实现了音量按钮的功能，通过音量按钮实现音量条的显示和隐藏。
### 后续工作：
1. 需要对音量按钮的用户交互体验进行提升。
2. 实现歌词动态显示，随着音乐播放进度实时高亮显示和定位，继续优化歌词和歌单的样式表。
## 日期：2025-8-17
### 完成的工作
1. 进行歌词动态显示的代码设计未完成，设计逻辑进行简化处理，暂定保持原来的歌词显示逻辑，将lrc文件中的歌词全部展示到文本框中。
2. 学习使用QSS对listWidget和TextEdit进行美化。
### 后续工作
1. 深入学习QSS，对界面进行美化（例如Slider和Label等）
2. 完善功能，使得ListWidget初始化时就存在歌曲
3. 增加功能，增加搜索功能，对ListWidget中的歌曲进行检索
4. 修改功能，修改音量按钮的功能，只有点击音量按钮才会弹出Slider

