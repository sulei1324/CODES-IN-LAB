clc;

clear all;

I1=imread('W:\lsu\movie\11-6movie\neutron\bouton\RGB-I2.bmp');

I2=imread('W:\lsu\movie\11-6movie\neutron\bouton\RGB-I3.bmp');


I=I1+I2;

imshow(I);