/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import java.util.List;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;

/**
 * @author Nick
 * @class wrapper class for xor nodes
 */
public class CipherXorWrapper {
    
    private String id;
    private String size;
    private inputs inputs;
    private Outputs outputs;
    private String X;
    private String Y;
        
    
    @XmlAttribute(name="size")
    public String getSize() {
        return this.size;
    }
    
    public void setSize(String Size) {
	this.size = Size;
    }
    
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
    
    
    @XmlElement(name="outputs")
    public Outputs getOutputs() {
        return this.outputs;
    }
    
    public void setOutputs(Outputs Outputs) {
	this.outputs = Outputs;
    }
    

}
