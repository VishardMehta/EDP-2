library('pracma')
a <- punif(45,0, 60, lower.tail = FALSE) #(a)
print(a)

b <- punif(30, 0, 60) - punif(20, 0, 60) #(b)
print(b)

a<-punif(45,0,60,lower.tail=FALSE)
print(a)

b<- punif(30,0,60)-punif(20,0,60)
print(b)

lambda <- 1/2

a <- dexp(3, lambda) #(a)
print(a)

x <- seq(0, 5, 0.001) #(b)
plot(x, dexp(x,lambda), type = "l", lwd = 2, col = "red")

c <- pexp(3, lambda) #(c)
print(c)

plot(x, pexp(x,lambda), type = "l", lwd = 2, col = "red") #(d)

x <- rexp(1000, lambda) #(e)

par(mfrow = c(2, 1))

hist(x)
plot(density(x))

alpha <- 2
beta <- 1/3

a <- pgamma(1, shape = alpha, scale = beta, lower.tail = FALSE) #(a)
print(a)

b <- qgamma(0.70, shape = alpha, scale = 1/3) #(b)
print(b)

f <- function(x,y){
  2*(2*x+3*y)/5
}

p <- integral2(f,0,1,0,1)

print(p$Q)

if(p$Q == '1'){ #(i)
  print("It is a joint density function")
}else{
  print("It is NOT a joint density function")
}

f1 <- function(y){ #(ii)
  f(1,y)
}

p <- integral(f1,0,1)
print(p)

f2 <- function(x){ #(iii)
  f(x,0)
}

p <- integral(f2,0,1)


print(paste("Marginal Distribution of h(y=0) is ",p))

gf <- function(x,y){ #(iv)
  x*y*f(x,y)
}

gfxy <- integral2(gf,0,1,0,1)

print(gfxy$Q)


f <- function(x,y){ #(i)
  (x+y)/30
}

x <- c(0:3)
y <- c(0:2)

M <- outer(x, y, f) #method1
print(M)


M <- matrix(c(f(0,y),f(1,y),f(2,y), f(3,y)),nrow = 4, ncol = 3, byrow = TRUE) #method 2
print(M)

if(sum(M)==1){ #(ii)
  print("f(x,y) is a joint mass function")
}else{
  print("f(x,y) is not a joint mass function")
}

gx <- apply(M, 1, sum) 
print(gx)

# 1 for row wise , 2 for col wise

hy <- apply(M, 2, sum) #(iv)
print(hy)

cp <- M[1,2]/hy[2] #(v)
print(cp)

Ex <- sum(x*gx) #(vi)
print(Ex)

Ey <- sum(y*hy)
print(Ey)

f1 <- function(x,y){ #method1
  x*y*f(x,y)
}
M1 <- outer(x,y,f1)
Exy <- sum(M1)
print(Exy)

Exx <- sum(x*x*gx)
varx <- Exx - Ex*Ex
print(varx)

Eyy <- sum(y*y*hy)
vary <- Eyy - Ey*Ey
print(vary)


covxy <- Exy - Ex*Ey
print(covxy)

#cor(xy)
cor <- covxy/sqrt(varx*vary)
print(cor)


n <- 100
df <- n-1
p <- rt(n,df)
print(p)
hist(p, col = "yellow")

n<-100
df<-c(2,20,25)

r1<-rchisq(n,df[1])
r2<-rchisq(n,df[2])
r3<-rchisq(n,df[3])
par(mfrow=c(1,3))
hist(r1,col="yellow")
hist(r2,col="hotpink")
hist(r3,col="green")


x <- seq(-6, 6, length = 100)
d1 <- dt(x,1)
d2 <- dt(x,4)
d3 <- dt(x,10)
d4 <- dt(x,30)

plot(x,d4,col="red")
lines(x,d2,col="yellow")
lines(x,d3,col="blue")
lines(x,d1,col="green")

f1 <- qf(0.95,10,20) #(i)
print(f1)

p1 <- pf(1.5, 10, 20) #(ii)
print(p1)
p2 <- 1-p1 #method1
print(p2) 
p2 <- pf(1.5, 10, 20, lower.tail = FALSE) #method2
print(p2)

f5 <- qf(c(0.25,0.5,0.75), 10, 20) #(iii)
print(f5)

r1 <- rf(1000,10,20) #(iv)
hist(r1)


data=read.csv(file.choose())
summary(data)

dim(data)
head(data,10)
x<-mean(data$Wall.Thickness)
hist(data$Wall.Thickness)
abline(v=x,col="red",lty = 2, lwd = 2)


s10 <- c() 

for(i in 1:10){
  s10[i] <- mean(sample(data$Wall.Thickness, 10, TRUE))
}
hist(s10)

s50<-c()
s500<-c()
s9000<-c()
for(i in 1:10000){
	s50[i]<-mean(sample(data$Wall.Thickness,50,TRUE))
	s500[i]<-mean(sample(data$Wall.Thickness,500,TRUE))
	s9000[i]<-mean(sample(data$Wall.Thickness,9000,TRUE))
	
}
par(mfrow=c(1,3))
hist(s50,col='pink')
abline(v=mean(s50), col = "red", lty = 2, lwd = 2)
hist(s500,col='violet')
abline(v=mean(s500), col = "red", lty = 2, lwd = 2)
hist(s9000,col='green')
abline(v=mean(s9000), col = "red", lty = 2, lwd = 2)


age <- c(58, 69, 43, 39, 63, 52, 47, 31, 74, 36)
cholesterol <- c(189, 235, 193, 177, 154, 191, 213, 165, 198, 181)

# Scatter plot
plot(age, cholesterol, main = "Cholesterol vs Age", xlab = "Age",ylab = "Cholesterol", 
     pch = 19, 
     col = "blue")

# Fit linear model
model <- lm(cholesterol ~ age)

# Add regression line
abline(model, col = "red", lwd = 2)

summary(model)

predicted_cholesterol <- predict(model, data.frame(age = 60))
print(predicted_cholesterol)



before <- c(145, 173, 158, 141, 167, 159, 154, 167, 145, 153)
after <-  c(155, 167, 156, 149, 168, 162, 158, 169, 157, 161)

# Perform a paired t-test
t.test(after, before,alternative="greater",mu=0, paired = TRUE,var.equal=FALSE,conf.level=0.95)


num_samples=1000
ssize=10
n=10
p=0.4

s_m<-replicate(num_samples,{
	sample<-rbinom(ssize,n,p)
	mean(sample)
})
print(mean(s_m))
print(var(s_m))
print(n*p)
print(n*p*(1-p)/ssize)


num_samples=1000
ssize=10
n=10
p=0.8

s_m<-replicate(num_samples,{
	sample<-rbinom(ssize,n,p)
	mean(sample)
})
hist(s_m)
x<-mean(s_m)
abline(v=x,col='red',lwd=2)
print(mean(s_m))
print(var(s_m))
print(n*p)
print(n*p*(1-p)/ssize)



lambda=4
n=50
num_samples=1000
sm1<-replicate(num_samples,{
	sample<-rpois(n,lambda)
	mean(sample)
})
print(mean(sm1))
print(var(sm1))
print(lambda)
print(lambda/n)


lambda=1.5
nor=c(10)
num_samples=1000

simulate<-function(n,num_samples){
	
	sm2<-replicate(num_samples,{
	sample<-rexp(n,lambda)
	mean(sample)
	})
	
	print(mean(sm2))
	print(var(sm2))
	hist(sm2,breaks=30)
	curve(dnorm(x,mean=mean(sm2),sd=sd(sm2)),add=TRUE,col='red',lwd=2)
	
	print(1/lambda)    
    print(1/((lambda^2)*n))
}	
	for(n in nor){
		simulate(n,num_samples)
	}
	
mu <- 70
sdv <- 10
ns <- 1000

sim_plot <- function(n, ns) {
  mns <- replicate(ns,{ 
  	sample<-rnorm(n, mean = mu, sd = sdv)
  	mean(sample)
  	})
  hist(mns, prob = TRUE, col = "skyblue", border = "white", breaks = 30)
  curve(dnorm(x, mean = mean(mns), sd = sd(mns)),
        add = TRUE, col = "red", lwd = 2)
  print(paste("n =", n, "Mean =",mean(mns)))
}
for (n in c(10, 50, 200)) sim_plot(n, ns)


shape <- 2
rate <- 1
ns <- 1000

sim_plot <- function(n, ns) {
  mns <- replicate(ns, mean(rgamma(n, shape = shape, rate = rate)))
  hist(mns, prob = TRUE, main = paste("Gamma Mean Dist (n =", n, ")"),
       xlab = "Mean", col = "skyblue", border = "white", breaks = 30)
  curve(dnorm(x, mean = mean(mns), sd = sd(mns)),
        add = TRUE, col = "red", lwd = 2)
  print(paste("n =", n, "Mean =", round(mean(mns), 2)))
  print(shape/rate) #mean
  print((shape/(rate)^2)/n) #var
}

for (n in c(100)) sim_plot(n, ns)
















