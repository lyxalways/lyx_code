from cyaron import * # 引入CYaRon的库
io = IO("test1.in", "test1.out") # 先新建一组数据
io.input_write(1, 2, 3) # 写入1 2 3到输入文件
io.input_writeln(4, 5, 6) # 写入4 5 6到输入文件并换行
io.output_write(1, 2, 3) # 写入1 2 3到输出文件
io.output_writeln(4, 5, 6) # 写入4 5 6到输出文件并换行
