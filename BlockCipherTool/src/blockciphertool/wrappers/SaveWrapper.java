/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import javax.xml.bind.annotation.XmlAttribute;

/**
 * @author Nick
 * @class Wrapper for the savefile. includes 3 cipher types for encrypt, decrypt and keygen.
 */
public class SaveWrapper {
    private CipherWrapper encryptionCipher;
    private CipherWrapper decryptionCipher;
    private CipherWrapper keygenCipher;
    private PropertiesWrapper props;
    
    @XmlAttribute(name="encrypt")
    public CipherWrapper getEncryptionCipher() {
	return this.encryptionCipher;
    }
    
    public void setEncryptionCipher(CipherWrapper EncryptionCipher) {
	this.encryptionCipher = EncryptionCipher;
    }
    
    @XmlAttribute(name="decrypt")
    public CipherWrapper getDecryptionCipher() {
	return this.decryptionCipher;
    }
    
    public void setDecryptionCipher(CipherWrapper DencryptionCipher) {
	this.decryptionCipher = DencryptionCipher;
    }
    
    @XmlAttribute(name="keygen")
    public CipherWrapper getKeygen() {
	return this.keygenCipher;
    }
    
    public void setKeygenCipher(CipherWrapper KeygenCipher) {
	this.keygenCipher = KeygenCipher;
    }
}
