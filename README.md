# 📚 Library Management System

一个的图书馆管理系统（C++ + SQLite3），区分 **书目（Book）** 与 **实体书（BookCopy）**，为后续功能扩展（借阅记录、推荐系统、多数据库支持等）打下良好基础。

---

## 🏗️ 系统架构概览(大概这样吧嘻)

```text
┌──────────────┐
│   UI / CLI   │   （后续可扩展 GUI / Web）
└──────┬───────┘
       │
┌──────▼───────┐
│  Service层   │   （业务逻辑，如借书、还书、推荐）
└──────┬───────┘
       │
┌──────▼───────────────┐
│        DAO 层         │
│  BookDAO / BookCopyDAO│
└──────┬───────────────┘
       │
┌──────▼──────────┐
│ DatabaseOperator │   （SQLite3 封装）
└──────┬──────────┘
       │
┌──────▼──────────┐
│     SQLite3     │
└─────────────────┘
```

---

## 📘 核心领域模型设计

### 1️⃣ Book（书目 / 书的抽象概念）

表示“**一种书**”，而不是具体可借阅的实体。

**典型字段：**

* `id`：书目唯一标识
* `title`：书名
* `author`：作者
* `category`：分类
* `publisher`：出版社

> 📌 Book 本身 **不可直接借阅**，仅用于描述书籍信息。

---

### 2️⃣ BookCopy（实体书 / 可借阅对象）

表示“**某一本具体的书**”，图书馆中真正可以被借走的单位。

**典型字段：**

* `copy_id`：实体书唯一编号（条码）
* `book_id`：所属 Book
* `status`：`available` / `borrowed`

> 📌 图书馆的借阅行为，**一定是基于 BookCopy，而不是 Book**。


---

## 🗃️ 数据库设计（目前设计后续可能会更改）

### 📄 book 表（书目表）

```sql
CREATE TABLE book (
    id TEXT PRIMARY KEY,
    title TEXT NOT NULL,
    author TEXT NOT NULL,
    category TEXT,
    publisher TEXT
);
```

### 📄 book_copy 表（实体书表）

```sql
CREATE TABLE book_copy (
    copy_id TEXT PRIMARY KEY,
    book_id TEXT NOT NULL,
    status TEXT NOT NULL, -- available / borrowed
);
```

---

## 📦 DAO 设计说明

### 📘 BookDAO（书目数据访问）

**职责：**

* 维护书目信息（增 / 删 / 改 / 查）
* 按分类、书名等方式检索书目

**不负责：**

* 借书 / 还书
* 库存状态

---

### 📕 BookCopyDAO（实体书数据访问）

**职责：**

* 管理实体书的增删
* 查询某书目的所有副本
* 查询当前可借副本

**负责“借阅”的数据基础，但不包含业务规则**。

---

## 🔧 DatabaseOperator 设计

`DatabaseOperator` 对 SQLite3 的 C API 进行统一封装，提供：

* 数据库打开 / 关闭
* SQL 执行（execute）
* 预编译语句（prepare）
* 查询封装
* 事务控制（BEGIN / COMMIT / ROLLBACK）

**目的：**

* 避免 DAO 层直接操作 sqlite3 API
* 方便后续切换数据库（如 MySQL）

---

### 🚀 后续计划--功能扩展规划TODO
#### 当前阶段目标
1. [x] 设计数据库表结构
2. [x] 集成SQLite3库
3. [ ] 实现DatabaseManager和BookDAO、UserDAO(未实现)
4. [ ] 数据迁移工具（txt → SQLite）
5. [ ] 密码加密
6. [x] 代码重构（FileOperator → DatabaseOperator）
7. [x] 添加BookCopy类来封装实体书
8. [ ] 重构其他相关代码
---
## 下一阶段大概计划

### 1.1 用户体验优化 
- [ ] **图书搜索功能增强**
- [ ] **用户注册功能**
- [ ] **密码找回功能**

### 1.2 数据备份
- [ ] **数据库备份功能**

### 1.3 借阅规则完善 
- [ ] **借阅数量限制**

- [ ] **续借功能**

- [ ] **预约功能**

### 1.4 推荐系统
- [ ] **基于自身借阅内容的推荐**
- [ ] **基于相似读者的推荐**
- [ ] **基于热门度 / 趋势的推荐**
- [ ] **基于类别平衡 / 多样性的推荐**
- [ ] **基于新书 / 时间因素的推荐**
- [ ] **混合推荐**

---

- [ ] 从SQLite迁移到MySQL
- [ ] 日志

---