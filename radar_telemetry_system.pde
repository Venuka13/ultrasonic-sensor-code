import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;

Serial myPort;
String angle="";
String distance="";
String data="";
String noObject;
float pixsDistance;
int iAngle, iDistance;
int index1=0;
int index2=0;

void setup() {
 size (1200, 700); // Sets screen size
 smooth();
 // Change "0" to match your Arduino's COM port index if it doesnt work 
 // If your Arduino IDE said COM3, write this:

myPort = new Serial(this, "COM5", 9600);


 myPort.bufferUntil('.'); 
}

void draw() {
 fill(0,4); 
 rect(0, 0, width, height-height*0.065); 
 fill(98,245,31); // Green color
 // Draw the radar elements
 drawRadar(); 
 drawLine();
 drawObject();
 drawText();
}

void serialEvent (Serial myPort) { 
 data = myPort.readStringUntil('.');
 data = data.substring(0,data.length()-1);
 index1 = data.indexOf(",");
 angle= data.substring(0, index1);
 distance= data.substring(index1+1, data.length());
 iAngle = int(angle);
 iDistance = int(distance);
}

void drawRadar() {
 pushMatrix();
 translate(width/2,height-height*0.074); 
 noFill();
 strokeWeight(2);
 stroke(98,245,31);
 // Draw the circular arcs
 arc(0,0,(width-width*0.0625),(width-width*0.0625),PI,TWO_PI);
 arc(0,0,(width-width*0.27),(width-width*0.27),PI,TWO_PI);
 arc(0,0,(width-width*0.479),(width-width*0.479),PI,TWO_PI);
 arc(0,0,(width-width*0.687),(width-width*0.687),PI,TWO_PI);
 // Draw the angle lines
 for (int i=30; i<=150; i+=30) {
   line(0,0,(-width/2)*cos(radians(i)),(-width/2)*sin(radians(i)));
 }
 popMatrix();
}

void drawLine() {
 pushMatrix();
 strokeWeight(9);
 stroke(30,250,60);
 translate(width/2,height-height*0.074);
 line(0,0,(height-height*0.12)*cos(radians(iAngle)),-(height-height*0.12)*sin(radians(iAngle)));
 popMatrix();
}

void drawObject() {
 pushMatrix();
 translate(width/2,height-height*0.074);
 strokeWeight(9);
 stroke(255,10,10); // Red color for objects
 pixsDistance = iDistance*((height-height*0.1666)*0.025); 
 if(iDistance<40){
   line(pixsDistance*cos(radians(iAngle)),-pixsDistance*sin(radians(iAngle)),(width/2)*cos(radians(iAngle)),-(width/2)*sin(radians(iAngle)));
 }
 popMatrix();
}

void drawText() {
 fill(98,245,31);
 textFont(createFont("Arial", 20));
 text("10cm", width/2+width*0.07, height-height*0.15);
 text("20cm", width/2+width*0.17, height-height*0.25);
 text("30cm", width/2+width*0.28, height-height*0.36);
 text("40cm", width/2+width*0.38, height-height*0.47);
 text("Angle: " + iAngle + " °", width*0.05, height-height*0.02);
 text("Distance: " + iDistance + " cm", width*0.4, height-height*0.02);
}
