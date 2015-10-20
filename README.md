#Soo

		Soo是简易的自制类C编程语言,支持基本的数据类型int,string,支持if,while语句类型,后端生成自制虚拟机[Lvm](https://github.com/Leviathan1995/Lvm)的目标代码。
		

##Building and Running:

###Linux,*nix,Mac OSX:
	$
	$
	$
	

##Example:


##Syntax：

* 支持的int,string数据类型
* 支持if,while语句类型
* 支持函数，目前暂不支持参数传递
* 注释使用"#"
* 每行代码结束无须使用";",直接换行即可
* 定义变量使用"var"关键字:
			
		var int i,j,k
		or
		vat string heart
* 定义函数使用"def"关键字:
		
		def heart()
		{
		
			...
			代码语句
			...
		}
* if条件语句:
		
		if(表达式)
		{
			...
			代码语句
			...
		}
* while条件语句:
	
		while(表达式)
		{
			...
			代码语句
			...
		}
* 终端输出使用print():

		print("hello world")
		or
		print(variable)


###Lincense:
	
		MIT
