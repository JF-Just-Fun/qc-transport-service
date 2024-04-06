-- Active: 1712244209215@@127.0.0.1@13306@QC_SERVER_DB
CREATE TABLE user(
    id int NOT NULL PRIMARY KEY AUTO_INCREMENT COMMENT 'Primary Key',
    create_time DATETIME COMMENT 'Create Time',
    uid CHAR(12) UNIQUE,
    name VARCHAR(16),
    gender BOOLEAN DEFAULT 0,
    password VARCHAR(16),
    email VARCHAR(255),
    phone VARCHAR(11),
    validate BOOLEAN DEFAULT 1
) COMMENT 'system user';

-- Active: 1712244209215@@127.0.0.1@13306@QC_SERVER_DB
CREATE TABLE role(
    id int NOT NULL PRIMARY KEY AUTO_INCREMENT COMMENT 'Primary Key',
    create_time DATETIME COMMENT 'Create Time',
    uid CHAR(12) UNIQUE,
    name VARCHAR(16),
    description TEXT,
    validate BOOLEAN DEFAULT 1
) COMMENT 'system role';