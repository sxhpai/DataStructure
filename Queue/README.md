### 本目录包含如下内容  

- 循环队列创建、插入元素、删除元素（）
- 链队列的创建、插入元素、删除元素（）

### 线性表的抽象数据类型  
> ADT 
> - 队列（Queue）  
>
> Data  
> 
> - 同线性表。元素具有相同的类型，相邻元素具有前驱和后继关系。  
> 
> Operation
> - InitQueue(*Q): 初始化操作，建立一个空队列Q。
> - DestroyQueue(*Q)：若队列存在，则销毁它。
> - ClearQueue(*Q)：将队列Q清空。
> - QueueEmpty(Q)：若队列Q为空，返回true，否则返回false。
> - GetHead(Q,*e)：若队列Q存在且非空，用e返回队列Q的队头元素。
> - <font color = 'red'>EnQueue(*Q,e)</font>：若队列Q存在，插入新元素e到队列Q中并成为队尾元素。
> - <font color = 'red'>DeQueue(*Q,*e)</font>：删除队列Q中对头元素，并用e返回其值。
> - QueueLength(Q)：返回队列Q的元素个数  
> 
> endADT    
> 
## 我的[队列](https://sxhpai.github.io/2022/03/30/DS/DS2/)博客
