#File:data.py
#By:Daisy
from string import *
from time import *
def read_order():
    f1=open("order.0.0","r")
    f2=open("order.1.1","r")
    f3=open("order.2.2","r")
    f4=open("order.0.3","r")
    a=f1.readlines()+f2.readlines()+f3.readlines()+f4.readlines()
    return a
def read_buyer():
    f1=open("buyer.0.0","r")
    f2=open("buyer.1.1","r")
    b=f1.readlines()+f2.readlines()
    return b
def read_good():
    f1=open("good.0.0","r")
    f2=open("good.1.1","r")
    f3=open("good.2.2","r")
    c=f1.readlines()+f2.readlines()+f3.readlines()
    return c
def order():
    orderid=raw_input("Please enter the orderid: ")
    s="orderid:"+orderid
    t1=time()
    a=read_order()
    for i1 in a:
        if s in i1:
            i2=split(i1)
            for i3 in i2:
                if "amount" in i3:
                    amount=i3
                elif "buyerid" in i3:
                    buyerid=i3
                elif "goodid" in i3:
                    goodid=i3
            b=read_buyer()
            for j1 in b:
                if buyerid in j1:
                    j2=split(j1)
                    for j3 in j2:
                        if "buyername" in j3:
                            buyername=j3
            c=read_good()
            for k1 in c:
                if goodid in k1:
                    k2=split(k1)
                    for k3 in k2:
                        if "good_name" in k3:
                            goodname=k3
                        elif "price" in k3 and (not "offprice" in k3):
                            price=k3
            total=eval(amount[7:])*eval(price[6:])
            t2=time()
            t=t2-t1
            print s
            print buyername
            print goodname
            print amount
            print price
            print "amount*price:",total
            print "time consuming:",t
            break
    else:
        print "Not found"
def buyer():
    buyerid=raw_input("Please enter the buyerid: ")
    s="buyerid:"+buyerid
    t1=time()
    a=read_buyer()
    for i1 in a:
        if s in i1:
            i2=split(i1)
            for i3 in i2:
                if "buyername" in i3:
                    buyername=i3
            b=read_order()
            c=read_good()
            n=0
            m=0
            for j1 in b:
                if s in j1:
                    n=n+1
                    j2=split(j1)
                    for j3 in j2:
                        if "amount" in j3:
                            amount=j3
                        elif "goodid" in j3:
                            goodid=j3
                    for k1 in c:
                        if goodid in k1:
                            k2=split(k1)
                            for k3 in k2:
                                if "price" in k3 and (not "offprice" in k3):
                                    price=k3
                    total=eval(amount[7:])*eval(price[6:])
                    m=m+total
            t2=time()
            t=t2-t1
            print s
            print buyername
            print "the total number of orders:",n
            print "the total amount of payments",m
            print "time consuming:",t
            break
    else:
        print "Not found"
def good():
    goodid=raw_input("Please enter the goodid: ")
    s="goodid:"+goodid
    t1=time()
    a=read_good()
    for i1 in a:
        if s in i1:
            i2=split(i1)
            for i3 in i2:
                if "good_name" in i3:
                    goodname=i3
            b=read_order()
            n=0
            m=0
            for j1 in b:
                if s in j1:
                    n=n+1
                    j2=split(j1)
                    for j3 in j2:
                        if "amount" in j3:
                            amount=j3
                    m=m+eval(amount[7:])
            t2=time()
            t=t2-t1
            print s
            print goodname
            print "the total number of orders:",n
            print "the total number of saled:",m
            print "time consuming:",t
            break
    else:
        print "Not found"
def main():
    t1=time()
    a=read_order()
    b=len(a)
    t2=time()
    t=t2-t1
    print b,t
    order()
    buyer()
    good()
main()

    
