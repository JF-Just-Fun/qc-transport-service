-- Active: 1712244209215@@127.0.0.1@13306@QC_SERVER_DB
CREATE TABLE user(
    id int NOT NULL PRIMARY KEY AUTO_INCREMENT COMMENT 'Primary Key',
    create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP COMMENT 'Create Time',
    uid CHAR(12) UNIQUE,
    name VARCHAR(16) UNIQUE,
    gender BOOLEAN DEFAULT 0,
    password VARCHAR(16),
    email VARCHAR(255),
    phone VARCHAR(11) UNIQUE,
    validate BOOLEAN DEFAULT 1
) COMMENT 'system user';

-- Active: 1712244209215@@127.0.0.1@13306@QC_SERVER_DB
CREATE TABLE role(
    id int NOT NULL PRIMARY KEY AUTO_INCREMENT COMMENT 'Primary Key',
    create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP COMMENT 'Create Time',
    uid CHAR(12) UNIQUE NOT NULL,
    name VARCHAR(16) NOT NULL,
    level INT(2) NOT NULL,
    description TEXT,
    validate BOOLEAN DEFAULT 1
) COMMENT 'system role';

-- 关联表 用户-角色
CREATE TABLE user_role(
    user_id INT NOT NULL,
    role_id INT NOT NULL,
    -- 外键约束
    FOREIGN KEY (user_id) REFERENCES user(id),
    FOREIGN KEY (role_id) REFERENCES role(id),
    -- 复合主键，确保唯一性
    PRIMARY KEY (user_id, role_id),
    -- 创建时间戳
    create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
) COMMENT 'Association between users and roles';

-- 接口表
-- CREATE TABLE api (
--     id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
--     name VARCHAR(50) UNIQUE, -- 接口名称或唯一标识
--     description TEXT,       -- 接口描述
--     method VARCHAR(10), -- HTTP 方法，如 GET, POST, PUT, DELETE
--     create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
-- );

-- 关联权限-角色 role - permission
-- CREATE TABLE role_permission (
--     role_id INT NOT NULL,
--     api_id INT NOT NULL,
--     -- 复合主键
--     PRIMARY KEY (role_id, api_id),
--     -- 外键约束
--     FOREIGN KEY (role_id) REFERENCES role(id),
--     FOREIGN KEY (api_id) REFERENCES api(id)
-- );
