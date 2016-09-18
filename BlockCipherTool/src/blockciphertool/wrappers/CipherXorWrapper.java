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
 *
 * @author Gigabyte
 */
public class CipherXorWrapper {
    
    private String id;
    private String size;
    private List<output> outputs;
    private List<input> inputs;
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

        @XmlElementWrapper(name="inputs")
    @XmlElement(name="input")
    public List<input> getInputs() {
        return this.inputs;
    }
    
    public void setInputs(List<input> Inputs) {
	this.inputs = Inputs;
    }
    
    
    @XmlElementWrapper(name="outputs")
    @XmlElement(name="output")
    public List<output> getOutputs() {
        return this.outputs;
    }
    
    public void setOutputs(List<output> Outputs) {
	this.outputs = Outputs;
    }
    

}
