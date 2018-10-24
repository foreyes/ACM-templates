eps默认设为1e-8
别把 a/(b*c) 写成 a/b*c
BFS的vis标记一定要在Continue判断之后,push之前打
全局变量记得初始化
线段树同时维护max和sum的时候，记得seg数组开多个，合并也得多个
树链剖分的修改与查询，给线段树的参数注意是deep小的节点在前，还得套一个dfn[x]
用lower_bound实现的LIS改成upper_bound即可是不降的。还有更多操作

cout<<Dicin_flow()<<" "<<tot_cost;
x = nx[x][y], y = ny[x][y]
以上两种沙雕写法是不可取的

检查不出错的时候记得反复确认题意。比如概率的一道傻逼题