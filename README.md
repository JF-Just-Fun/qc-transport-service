# service

## development

1. 下载依赖

2. 使用cmake生成Makefile文件

> 如果有问题，注意删除cmakeCache之类的文件。

```bash
mkdir -p build # 递归创建build文件夹
cd build
cmake ..
```

3. 构建可执行文件
```bash
make .
```

4. 运行服务
```bash
./qc-transport-service
```

## env 环境变量

1. BRANCH_NAME
当前分支名称，根据github的分支，调用不同的config.json

## 生成 model
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
