/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;

/**
 * @author Nick
 * @class wrapper for subkeys, used in the keygen, not to be confused with cipher keys which are purely for front end visualisation
 */
public class CipherSubkeyWrapper {
    
    private String id;
    private String X;
    private String Y;
    private inputs inputs;
    
    
    
    @XmlAttribute(name="ID")
    public String getId() {
	return this.id;
    }
    
    public void setId(String Id) {
	this.id = Id;
    }
    
    @XmlElement(name="X")
    public String getX() {
        return this.X;
    }
    
    public void setX(String x) {
	this.X = x;
    }
    
    @XmlElement(name="Y")
    public String getY() {
        return this.Y;
    }
    
    public void setY(String y) {
	this.Y = y;
    }
    
    @XmlElement(name="inputs")
    public inputs getInputs() {
        return this.inputs;
    }
    
    public void setInputs(inputs Inputs) {
	this.inputs = Inputs;
    }
}
