### 概述
&emsp;&emsp;Nebula是一个C\+\+语言开发的事件驱动型的TCP协议分布式网络框架，支持包括proto3、http、https、websocket多种应用层通信协议。开发Nebula框架的目的是提供一种基于C\+\+快速构建高性能的分布式服务。Nebula自身核心代码只有2万行左右（不计算proto文件生成的代码）。

&emsp;&emsp;Nebula可以作为单个高性能TCP服务器使用，不过基于Nebula搭建分布式服务才能真正体现其价值。为了能快速搭建分布式服务，开发了包括各种类型服务的NebulaBootstrap解决方案。

&emsp;&emsp;Nebula是一个产线级的框架和分布式解决方案项目，适用于即时通讯、数据采集、实时计算、消息推送等应用场景，也适用于web后台服务。Nebula已有即时通讯、埋点数据采集及实时分析的生产应用案例。

### 选择Nebula的理由
1.  Nebula源于互联网生产线业务，却高于业务，适用于即时通讯、数据采集、实时计算、消息推送、web后台服务等多个业务领域。
2.  Nebula是一个高性能C++网络框架，却又不仅是一个网络框架，还是一个十分通用的业务框架。选择Nebula，不必在网络框架之上再做业务框架封装。
3.  Nebula依赖的第三方库很少，开发和部署无成本。所依赖的protobuf、hiredis是无论选择什么框架都会用到的第三方库，libev和crypto++又是轻量到可以忽略不计。
4.  无锁设计，无须考虑线程安全问题，无须考虑进程或线程模型，专注写业务代码更得心应手。
5.  详细的文档，入门简单，扩展容易。

### Nebula由来

&emsp;&emsp;Nebula从一个从2016年5月至今在生产环境稳定运行的IM底层框架Starship发展而来。Nebula跟Starship框架（Bwar一人独立开发）有20%左右的结构相似度，是基于Starship经验全新开发，可以认为Nebula(C++11)是Starship(C++98)的一个高级进化版本，具有Starship的所有优点，没有Starship的所有已发现的缺点，同时提供了更多高级功能。基于Nebula的第一个埋点数据采集和实时分析项目应用Nebio于2018年7月底上线并稳定运行，Bwar还准备开发基于Nebula的IM应用Nebim。

### 大型系统构建原则：
* 可用性
* 性能
* 可靠性
* 可扩展性
* 易管理
* 成本

### Nebula的功能
* 支持http、protobuf、websocket等协议通信
* 支持ssl连接加密
* 微服务框架
* IoC容器
* 动态服务更新
* 服务注册
* 服务发现
* 服务监控
* 配置管理
* 动态路由
* 负载均衡
* 过载保护
* 故障熔断
* 故障检测和恢复
* 数据统计
* 分层服务
* 认证和鉴权
* 分布式日志跟踪

### 还有更多
&emsp;&emsp;现知名度较高的网络框架以rpc框架为主，且大都是大厂开源产品，有较大量应用案例，更有不少知名度低些却不乏开发者关注的网络框架。这些知名度高的网络框架大都只有简单的rpc功能，少数带有服务治理、配置管理、监控上报、动态路由等功能，又或只开源了基础rpc功能未开源服务治理等功能。而Nebula有完整的分布式服务所需功能，且全部开源。

&emsp;&emsp;许多简单联网应用只部署在一台或几台服务器上，启动个server程序，通过rpc客户端或配置nginx代理以轮询方式访问，写个shell脚本监控进程是否存在，挂了就拉起就可以满足业务需求了，这样的应用场景简单rpc确实够用了，大部分开源网络框架都可以满足需求。Nebula更是轻而易举满足这种需求。

&emsp;&emsp;然而，对于需要高可靠性，高并发和高扩展性的应用场景，大部分已知的网络框架都是不满足需求的，选型某个网络框架后，开发团队往往还需要基于这些网络框架之上花大量时间费很大力气开发业务框架构建分布式服务。选择Nebula就没有这样的麻烦，Nebula的一站式服务不仅让只需布几个独立server就可以解决的业务变得更轻而易举，还让需要分布式部署的复杂业务也轻轻松松。

&emsp;&emsp;异步回调模型在大中型高并发服务系统比多线程更加流行，除了多线程的死锁问题外，异步还能解决多线程下，线程反复切换导致不必要的开销的问题：每个线程都需要一个独立的栈空间，在多线程并行运行的时候，这些栈的数据可能需要来回的拷贝，这额外消耗了CPU。由于每个操作都是非阻塞的，所以Nebula可以只用一个进程，就处理大量并发的请求。因为只有一个进程，所有的数据处理，其顺序都是固定的，不可能出现多线程中，两个函数的语句交错执行的情况，因此也不需要各种“锁”。从这个角度看，异步非阻塞的技术，是大大简化了开发的过程。由于只有一个线程，也不需要有线程切换之类的开销，所以异步非阻塞成为很多对吞吐量、并发有较高要求的系统首选。

&emsp;&emsp;Nebula每个进程基于事件驱动的异步回调，性能极高，单个进程做压力测试时可以将CPU利用率达到100%。另一方面，Nebula的多进程模型可以充分利用服务器多CPU多核资源，进程数量可配置，并提供CPU绑定功能，若配置与CPU核数相同的进程数量，并让每个Worker进程都绑定CPU运行，在足够的并发量下可以达到服务器资源的极致利用。

&emsp;&emsp;分布式系统在业务需求的功能以外，还需要增加额外很多非功能的需求。这些非功能需求，往往都是为了系统能稳定可靠运行而去设计和实现的，一般都会让你的代码更加复杂，也会耗费大量时间，用Nebula将为你解决业务需求之外的功能。



