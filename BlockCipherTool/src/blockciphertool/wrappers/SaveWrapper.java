/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementDecl;
import javax.xml.bind.annotation.XmlRegistry;
import javax.xml.bind.annotation.XmlSeeAlso;
import javax.xml.namespace.QName;

/**
 * @author Nick
 * @class Wrapper for the savefile. includes 3 cipher types for encrypt, decrypt and keygen.
 */
@XmlSeeAlso(CipherWrapper.class)
@XmlRegistry
public class SaveWrapper {
    private CipherWrapper encryptionCipher = new CipherWrapper();
    private CipherWrapper decryptionCipher = new CipherWrapper();
    private CipherWrapper keygenCipher = new CipherWrapper();
    private PropertiesWrapper properties = new PropertiesWrapper();
    
    private final static QName _Encrypt_QNAME = new QName("", "encrypt");
    private final static QName _Decrypt_QNAME = new QName("", "decrypt");
    private final static QName _Keygen_QNAME = new QName("", "keygen");
    private final static QName _Properties_QNAME = new QName("", "properties");

    
    
    @XmlElementDecl(namespace="", name="encrypt")
    public JAXBElement<CipherWrapper> getEncryptionWrappedCipher() {
	return new JAXBElement<CipherWrapper>(_Encrypt_QNAME, CipherWrapper.class, null, this.encryptionCipher);
    }
    
    public CipherWrapper getEncryptionCipher() {
	return this.encryptionCipher;
    }
    
    public void setEncryptionCipher(CipherWrapper EncryptionCipher) {
	this.encryptionCipher = EncryptionCipher;
    }
    
    @XmlElementDecl(namespace="", name="decrypt")
    public JAXBElement<CipherWrapper> getDecryptionWrappedCipher() {
	return new JAXBElement<CipherWrapper>(_Decrypt_QNAME, CipherWrapper.class, null, this.decryptionCipher);
    }
    
    public CipherWrapper getDecryptionCipher() {
	return this.decryptionCipher;
    }
    
    public void setDecryptionCipher(CipherWrapper DecryptionCipher) {
	this.decryptionCipher = DecryptionCipher;
    }
    
    @XmlElementDecl(namespace="", name="keygen")
    public JAXBElement<CipherWrapper> getWrappedKeygen() {
	return new JAXBElement<CipherWrapper>(_Keygen_QNAME, CipherWrapper.class, null, this.keygenCipher);
    }
    
    public CipherWrapper getKeygen() {
	return this.keygenCipher;
    }
    
    public void setKeygenCipher(CipherWrapper KeygenCipher) {
	this.keygenCipher = KeygenCipher;
    }
    
    @XmlElementDecl(namespace="", name="properties")
    public JAXBElement<PropertiesWrapper> getWrappedProperties() {
	return new JAXBElement<PropertiesWrapper>(_Properties_QNAME, PropertiesWrapper.class, null, this.properties);
    }
    
    public PropertiesWrapper getProperties() {
	return this.properties;
    }
    
    public void setProperties(PropertiesWrapper Properties) {
	this.properties = Properties;
    }
}
