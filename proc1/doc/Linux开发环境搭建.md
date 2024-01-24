#### 安装CentOS7 WSL子系统

- 安装WSL（自行搜索）
- 下载[CentOS7安装包](https://github.com/mishamosher/CentOS-WSL/releases/download/7.9-2111/CentOS7.zip)，解压后双击`CentOS7.exe`进行安装，注意安装后无法移动位置
- 安装后可通过双击`CentOS7.exe`登录系统，也可通过`wsl`命令。推荐使用`Windows Terminal`管理不同终端

#### 开发环境搭建

- VS Code安装WSL插件，连接CentOS7
- 将`/etc/resolv.conf`中的`nameserver`改成跟主机中的一致，当前为`192.168.2.1`
- 安装gcc及其他工具
```
yum -y update
yum -y install gcc gcc-c++ gdb unzip tmux wget pigz
```
- 升级gcc
```
yum -y install centos-release-scl
yum -y install devtoolset-9-gcc devtoolset-9-gcc-c++ devtoolset-9-gdb devtoolset-9-libasan-devel
scl enable devtoolset-9 bash
echo source /opt/rh/devtoolset-9/enable > /etc/profile.d/enable-devtoolset-9.sh
```
- 安装git
```
yum -y install https://packages.endpointdev.com/rhel/7/os/x86_64/endpoint-repo.x86_64.rpm
yum -y install git
```
- 安装cmake
```
wget https://github.com/Kitware/CMake/releases/download/v3.25.2/cmake-3.25.2-linux-x86_64.sh
chmod +x cmake-3.25.2-linux-x86_64.sh
./cmake-3.25.2-linux-x86_64.sh --prefix=/usr --skip-license
```
- 安装Ninja
```
wget https://github.com/ninja-build/ninja/releases/download/v1.11.1/ninja-linux.zip
unzip ninja-linux.zip -d /usr/bin
```
- 安装cgdb（可选）
```
# 安装编译依赖项
yum -y install autoconf automake libtool flex bison ncurses-devel texinfo readline-devel
# 下载cgdb源码、解压、编译
wget https://cgdb.me/files/cgdb-0.8.0.tar.gz
tar xf cgdb-0.8.0.tar.gz
cd cgdb-0.8.0
./configure
make && make install
```
- 安装调试信息（可选）
```
debuginfo-install libgcc-4.8.5-44.el7.x86_64 libstdc++-4.8.5-44.el7.x86_64
```
- 修改单个进程可打开文件数量的限制
```
# 在/etc/security/limits.conf中增加：
root             hard    nofile          10000
root             soft    nofile          10000
# 在/etc/pam.d/login中增加：
session    required     pam_limits.so
```
- 修改core dump文件名格式和大小限制
```
# 在/etc/sysctl.conf中增加：
kernel.core_pattern=%e.%t.core
# 在~/.bashrc中增加：
ulimit -c unlimited
```

#### 编译服务器

- git克隆工程
- 在工程根目录下运行以下命令：
```
cmake -B build/debug -D CMAKE_BUILD_TYPE=Debug -G Ninja
cmake --build build/debug
cmake --install build/debug
```

#### 服务端问题排查

- [安装`kubectl`](https://kubernetes.io/docs/tasks/tools/install-kubectl-linux/)
```
curl -L "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl" -o /usr/local/bin/kubectl
chmod +x /usr/local/bin/kubectl
```

- 安装`jq`
```
wget https://github.com/jqlang/jq/releases/download/jq-1.6/jq-linux64
chmod +x jq-linux64
mv jq-linux64 /usr/local/bin/jq
```

- 将以下内容添加到`~/.bashrc`
```
alias k='kubectl'
alias kls='kubectl get pods'
alias kcp='kubectl cp --retries=-1'

kl() {
    pod=$1
    kubectl exec -it $pod -- bash
}

kd() {
    test $# -lt 2 && return
    pod=$1
    shift
    for file in "$@"; do
        kubectl cp --retries=-1 $pod:$file $file
    done
}

kf() {
    port=$1
    for pod in $(kubectl get pods --no-headers | cut -d ' ' -f 1); do
        kubectl get pod $pod -oyaml | grep \"port\":\"$port\" > /dev/null && echo $pod
    done
}

kp() {
    pod=$1
    json=$(kubectl get pod $pod -oyaml | grep externalAddresses)
    json=${json:36:-1}
    json=$(echo $json | jq .externalAddresses[0])
    echo $json | jq -r '[.ip, .ports[0].port] | join(":")'
}
```
