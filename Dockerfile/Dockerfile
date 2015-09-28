FROM library/centos:latest

COPY . /src

RUN rpm -iUvh http://dl.fedoraproject.org/pub/epel/7/x86_64/e/epel-release-7-5.noarch.rpm && yum -y update && yum -y install python-pip && pip install sseclient && yum install -y vim

CMD ["/bin/bash"]