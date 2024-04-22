# service

## 生成model
先创建好数据库，然后执行指令：

```shell
# 将生成好的model文件放到./models目录下
drogon_ctl create model ./models
```


## data code
0: 成功
1: 失败
2: 访问频繁
3: 权限不足
4: 参数错误

## 登录
1. login
输入name和password登录

2. registry
输入： `gender`, `name`, `email`, `password`, `telephone`进行注册

3. info
登录过之后会存session，可以直接获取用户信息

4. info/:id
查询指定id的用户信息
