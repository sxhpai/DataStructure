
### 本目录包含如下内容  

- 二叉树的创建、遍历（BiTree.c）
- 二叉树的线索化,与线索二叉树的遍历（BiThrTree.c）
- 大话数据结构所本章所有代码（AllTree.c）

### 树的抽象数据类型  

ADT	

- 树（tree）

Data

- 树是由一个根节点和若干棵子树构成。树中结点具有相同数据类型及层次关系。

Operstion

- InitTree( *T )：构造空树。
- DestroyTree( *T )：销毁树 T。
- CreateTree( *T,  definition )：按 definition 中给出树的定义来构造树。
- ClearTree( *T )：若树T存在，则将树T清为空树。
- TreeEmpty( T )：若 T 为空树，返回 true，否则返回 false。
- TreeDepth( T )：返回 T 的深度。
- Root( T )：返回T的根节点。
- Value( T, cur_e )：cur_e 是树 T 中一个结点，返回此节点的值。
- Assign( T, cur_e, value )：给树 T 的结点 cur_e 赋值为 value。
- Parent( T, cur_e )：若cur_e是树 T 的非根结点，则返回它的双亲，否则返回空。
- LeftChild( T, cur_e )：若cur_e是树T的非叶结点，则返回它的最左孩子，否则返回空。
- RightSibling( T, cur_e )：若 cur_e 有兄弟，则返回它的左右兄弟，否则返回空。
- InsertChild( *T, *p, i, c )：其中 p 指向树 T 的某个结点，i 为所指结点 p 的度加上1，非空树 c 与 T  不相交，操作结果为插入 c 为数 T 中 p 指结点的第 i 棵子树。
- DeleteChild( *T, *p, i)：其中 p 指向树 T 个某个结点，i 为所指结点 p 的度， 操作结果为删除 T 中 p 所指结点的第 i 棵子树。

endADT

## 我的[树](https://sxhpai.github.io/2022/04/04/DS/DS4/)博客
