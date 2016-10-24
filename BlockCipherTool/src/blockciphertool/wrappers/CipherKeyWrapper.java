/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;

import java.util.List;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlElementWrapper;

import blockciphertool.wrappers.inputs;
import blockciphertool.wrappers.Outputs;
import javax.xml.bind.annotation.XmlAttribute;

/**
 * @author nick
 * @class Save wrapper class for key inputs
 */
public class CipherKeyWrapper {
    
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
