/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlAttribute;
/**
 *
 * @author nick
 */

@XmlRootElement(name="input")
public class input {
    
    private String connectorID;
    private String size;
    
    @XmlAttribute(name="connectorID")
    public String getConnectorID() {
        return this.connectorID;
    }
    
    public void setConnectorID(String ConnectorID) {
        this.connectorID = ConnectorID;
    }
    
    @XmlAttribute(name="size")
    public String getSize() {
        return this.size;
    }
    
    public void setSize(String Size) {
        this.size = Size;
    }
    
    
}
