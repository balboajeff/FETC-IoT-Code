/**
 * HTTP Client. 
 * 
 * Starts a network client that connects to a server on port 80,
 *The sketch connects to a feed on data.sparkfun.com and builds a feed from there
 *
 http://data.sparkfun.com/output/q58gwmpVaOfm0jw1z7DX/latest  is the example string
 */


import processing.net.*;

String publicKey="DJqz9MZQrjijQXKpDoj2";//put your public key in the quotation marks
//String todaysDate="12-27-2014";//uncomment to enable the page filters for larger data sets.The date will determine the data returned
String[] data;
int[] subData;

void setup() 
{
  size(1079, 300);
  fill(200);
}

void draw() 
{
   background(50);
  
  String lines[]=loadStrings("http://data.sparkfun.com/output/"+publicKey+"/latest");
  //Uncomment the line below this to enable  the return of larger data sets
  //String lines[]= loadStrings("http://data.sparkfun.com/output/"+publicKey+"?gte%5Btimestamp%5D="+todaysDate+"");
  data=lines;
  if (data.length >= 0) {
    subData =int (split(data[1], ","));
  }
  textSize(50);
  text(subData[0], 25, 50);
  rect(25, 75, subData[0], 200);
}