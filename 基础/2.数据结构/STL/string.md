### string
- `size()`与`empty()`是所有容器公有的方法
- `length()`，与`size()`等价
- `clear()`
- `substr(int start, int len)` start为子串起始下标，len为子串长度。len缺省则至字符串末尾
- `c_str()` 用于printf输出string风格字符串，`printf("%s", str.c_str());`
- `operator[]`/`operator+=`