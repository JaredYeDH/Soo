#  Soo-Complier


---
<h4>By:Leviathan
<h3>Date:

        2015年3月至今

<h3>Process:

<h5>Configure boost:

        在词法分析Lexer.h 中使用了boost::regex类 ，所以需要配置boost库。
<h5>Module：

        API:    串联各个模块
        Lexer:  词法分析
        Parser: 语法分析
        Error:  错误提示
        SymbolTable: 符号表系统
        x86:    生成目标机器代码
        
<h3>Support Syntax:


        支持数据类型：int ,char ,float,string
        支持语句结构：if，while,for
