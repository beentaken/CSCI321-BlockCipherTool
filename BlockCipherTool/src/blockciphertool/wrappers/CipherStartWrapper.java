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
 * @class wrapper for start nodes, not used by backend, just for visualisation of gui
 */
public class CipherStartWrapper {
        
    private String id;
    private String X;
    private String Y;
    private Outputs outputs;
    
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
    
    @XmlElement(name="outputs")
    public Outputs getOutputs() {
        return this.outputs;
    }
    
    public void setOutputs(Outputs Outputs) {
	this.outputs = Outputs;
    }
}
