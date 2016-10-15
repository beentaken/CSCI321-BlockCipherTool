/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import javax.xml.bind.annotation.XmlElement;

/**
 * @author Nick
 * @class a wrapper class for connections coming from a node
 */
public class CipherConnectionFrom {
    private String connectionPort;
    private String connectionBox;
    private String fromId;
    
    @XmlElement(name="connectionPort")
    public String getConnectionPort() {
        return this.connectionPort;
    }
    
    public void setConnectionPort(String ConnectionPort) {
	this.connectionPort = ConnectionPort;
    }
    
     
    @XmlElement(name="connectionBox")
    public String getConnectionBox() {
        return this.connectionBox;
    }
    
    public void setConnectionBox(String ConnectionBox) {
	this.connectionBox = ConnectionBox;
    }
    
   
    
    @XmlElement(name="fromId")
    public String getFromId() {
        return this.fromId;
    }
    
    public void setFromId(String FromId) {
	this.fromId = FromId;
    }

}
