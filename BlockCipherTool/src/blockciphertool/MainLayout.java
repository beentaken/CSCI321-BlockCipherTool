/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import blockciphertool.wrappers.CipherConnectionWrapper;
import blockciphertool.wrappers.CipherFunctionWrapper;
import blockciphertool.wrappers.CipherWrapper;
import blockciphertool.wrappers.CipherXorWrapper;
import blockciphertool.wrappers.PropertiesWrapper;

import java.io.IOException;
import javafx.event.ActionEvent;
import javafx.event.EventDispatchChain;

import javafx.event.EventHandler;
import javafx.event.EventType;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Point2D;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.SplitPane;
import javafx.scene.input.ClipboardContent;
import javafx.scene.input.DragEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.TransferMode;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;

import blockciphertool.wrappers.SaveLoadTool;
import blockciphertool.wrappers.pboxWrapper;
import blockciphertool.wrappers.sboxWrapper;
import java.util.ArrayList;
import java.util.List;
import javafx.scene.Node;
import javafx.scene.control.Tab;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;

/**
 *
 * @author Alex, Nick
 */
public class MainLayout extends AnchorPane{
    
    @FXML SplitPane base_pane;
    @FXML SplitPane decbase_pane;
    @FXML SplitPane keybase_pane;
    @FXML AnchorPane decrypt_pane;
    @FXML AnchorPane encrypt_pane;
    @FXML AnchorPane key_pane;
    @FXML VBox node_list;
    @FXML VBox dnode_list;
    @FXML VBox key_list;
    @FXML TextField numRounds;
    @FXML TextField blockSize;
    @FXML TextField keySize;
    @FXML TextField numRounds2;
    @FXML TextField blockSize2;
    @FXML TextField keySize2;
    @FXML TextField keyNum;
    @FXML Tab encrypt_tab;
    @FXML Tab decrypt_tab;
    @FXML Tab key_tab;
    
    private DragIcon mDragOverIcon = null;
    private DragIcon mDecDragOverIcon = null;
    private DragIcon mKeyDragOverIcon = null;
    
    public enum tabType {
        encrypt, decrypt, key
    }
    private tabType tabMode;
    
    //event handlers for encrypt pane
    private EventHandler<DragEvent> mIconDragOverRoot=null;
    private EventHandler<DragEvent> mIconDragDropped=null;
    private EventHandler<DragEvent> mIconDragOverLeftPane=null;
    
    //event handlers form dragging in decrypt pane
    private EventHandler<DragEvent> mDecIconDragOverRoot=null;
    private EventHandler<DragEvent> mDecIconDragDropped=null;
    private EventHandler<DragEvent> mDecIconDragOverLeftPane=null;
    
    //event handlers form dragging in key pane
    private EventHandler<DragEvent> mKeyIconDragOverRoot=null;
    private EventHandler<DragEvent> mKeyIconDragDropped=null;
    private EventHandler<DragEvent> mKeyIconDragOverLeftPane=null;
    
    //for encrypt cipher
    private List<PboxNode> pboxs;
    private List<SboxNode> sboxs;
    //private List<CipherFunctionWrapper> functions;
    private List<XorNode> xors;
    private List<NodeLink> connections;
    private PropertiesWrapper properties;
    
    //for decrypt cipher
    private List<PboxNode> decpboxs;
    private List<SboxNode> decsboxs;
    //private List<CipherFunctionWrapper> decfunctions;
    private List<XorNode> decxors;
    private List<NodeLink> decconnections;
    
    //for key generator
    private List<PboxNode> keypboxs;
    private List<SboxNode> keysboxs;
    //private List<CipherFunctionWrapper> keyfunctions;
    private List<XorNode> keyxors;
    private List<NodeLink> keyconnections;
    private List<subKey> subKeys;
    
    private int idCounter;
    private int keyIdCounter;
    
    //for encrypt cipher
    private boolean startExists;
    private boolean endExists;
    private boolean eKeyExists;
    
    //for decrypt cipher
    private boolean decstartExists;
    private boolean decendExists;
    private boolean dKeyExists;
    
    //for key generator
    private boolean keystartExists;
    
    
    
    /**
    * @author Alex
    */
    public MainLayout() {

        FXMLLoader fxmlLoader = new FXMLLoader(
            getClass().getResource("/blockciphertool/FXMLDocument.fxml")
        );

        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();

        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
        
        idCounter = 1;
        keyIdCounter = 1;
        startExists = false;
        endExists = false;
        decstartExists = false;
        decendExists = false;
        keystartExists = false;
        eKeyExists = false;
        dKeyExists = false;
        tabMode = tabType.encrypt;
    }
    
    /**
    * @author Alex
    */
    public void updateIdCounter() {
        idCounter++;
    }
    
    /**
    * @author Alex
    */
    public void updateKeyIdCounter() {
        keyIdCounter++;
    }
    
    /**
    * @author Alex
    */
    @FXML
    private void initialize() {
	//nicks code for save/load
	
	
	
	//SaveLoadTool saveController = new SaveLoadTool();
	//saveController.saveAsXml("save.xml");
	
	
        //Add one icon that will be used for the drag-drop process
        //This is added as a child to the root AnchorPane so it can be 
        //visible on both sides of the split pane.
        mDragOverIcon = new DragIcon();
	
        mDragOverIcon.setVisible(false);
        mDragOverIcon.setOpacity(0.65);
        getChildren().add(mDragOverIcon);  
        
        //same for decrypt
        mDecDragOverIcon = new DragIcon();
	
        mDecDragOverIcon.setVisible(false);
        mDecDragOverIcon.setOpacity(0.65);
        getChildren().add(mDecDragOverIcon);  
        
        //same for keygen
        mKeyDragOverIcon = new DragIcon();
	
        mKeyDragOverIcon.setVisible(false);
        mKeyDragOverIcon.setOpacity(0.65);
        getChildren().add(mKeyDragOverIcon);  

        //populate left pane of encrypt tab with multiple colored icons for testing
        for (int i = 0; i < 6; i++) {

            DragIcon icn = new DragIcon();
            addDragDetectionIcon(icn);
            icn.setType(DragNodeType.values()[i]);
            
            switch (i) {
                case 0:
                    icn.Icon_Tooltip.setText("Start: Node that represents the input for the cipher. (Required in cipher)");
                break;
                case 1:
                    icn.Icon_Tooltip.setText("Permutation box: used to permute or transpose bits from input(s) to output(s)");
                break;
                case 2:
                    icn.Icon_Tooltip.setText("Substitution box: takes some input bits and replaces them with different output bits");
                break;
                case 3:
                    icn.Icon_Tooltip.setText("XOR: a bitwise XOR across two inputs");
                break;
                case 4:
                    icn.Icon_Tooltip.setText("End: Node that represents the output for the cipher. (Required in cipher)");
                break;
                case 5:
                    icn.Icon_Tooltip.setText("subKey: Node that represents the  SubKey to be used in the cipher. (Required in cipher)");
                break;
                    
            }
            
            node_list.getChildren().add(icn);
        }
        
        //populate left pane of encrypt tab with multiple colored icons for testing
        for (int i = 0; i < 6; i++) {

            DragIcon icn = new DragIcon();
            addDecDragDetectionIcon(icn);
            icn.setType(DragNodeType.values()[i]);
            
            switch (i) {
                case 0:
                    icn.Icon_Tooltip.setText("Start: Node that represents the input for the cipher. (Required in cipher)");
                break;
                case 1:
                    icn.Icon_Tooltip.setText("Permutation box: used to permute or transpose bits from input(s) to output(s)");
                break;
                case 2:
                    icn.Icon_Tooltip.setText("Substitution box: takes some input bits and replaces them with different output bits");
                break;
                case 3:
                    icn.Icon_Tooltip.setText("XOR: a bitwise XOR across two inputs");
                break;
                case 4:
                    icn.Icon_Tooltip.setText("End: Node that represents the output for the cipher. (Required in cipher)");
                break;
                case 5:
                    icn.Icon_Tooltip.setText("subKey: Node that represents the  SubKey to be used in the cipher. (Required in cipher)");
                break;
                    
            }
            
            dnode_list.getChildren().add(icn);
        }
        
        for (int i = 0; i < 5; i++) {

            DragIcon icn = new DragIcon();
            addKeyDragDetectionIcon(icn);
            icn.setType(DragNodeType.values()[i]);
            if (i == 4)
                icn.setType(DragNodeType.values()[i+2]);
            
            switch (i) {
                case 0:
                    icn.Icon_Tooltip.setText("Start: Node that represents the input for the cipher. (Required in cipher)");
                break;
                case 1:
                    icn.Icon_Tooltip.setText("Permutation box: used to permute or transpose bits from input(s) to output(s)");
                break;
                case 2:
                    icn.Icon_Tooltip.setText("Substitution box: takes some input bits and replaces them with different output bits");
                break;
                case 3:
                    icn.Icon_Tooltip.setText("XOR: a bitwise XOR across two inputs");
                break;
                case 4:
                    icn.Icon_Tooltip.setText("subKey: Node that represents the  SubKey to be used in the cipher. (Required in cipher)");
                break;
                    
            }
            
            key_list.getChildren().add(icn);
        }
        
        
        
        
        buildDragHandlers();
        buildDecDragHandlers();
        buildKeyDragHandlers();
        
        pboxs = new ArrayList<PboxNode>();
        sboxs = new ArrayList<SboxNode>();
        xors = new ArrayList<XorNode>();
        connections = new ArrayList<NodeLink>();
        properties = new PropertiesWrapper();
        
        decpboxs = new ArrayList<PboxNode>();
        decsboxs = new ArrayList<SboxNode>();
        decxors = new ArrayList<XorNode>();
        decconnections = new ArrayList<NodeLink>();
        
        keypboxs = new ArrayList<PboxNode>();
        keysboxs = new ArrayList<SboxNode>();
        keyxors = new ArrayList<XorNode>();
        keyconnections = new ArrayList<NodeLink>();
        subKeys = new ArrayList<subKey>();
    }
    
    /**
    * @author Alex
    * Adds Drag detection to the drag nodes in the encrypt tab
    */
    private void addDragDetectionIcon(DragIcon dragIcon) {
        
        dragIcon.setOnDragDetected(new EventHandler <MouseEvent>() {
            
            @Override
            public void handle(MouseEvent event) {
                
                base_pane.setOnDragOver(mIconDragOverRoot);
                encrypt_pane.setOnDragOver(mIconDragOverLeftPane);
                encrypt_pane.setOnDragDropped(mIconDragDropped);
                
                DragIcon icn = (DragIcon) event.getSource();
                
                mDragOverIcon.setType(icn.getType());
                mDragOverIcon.relocateToPoint(new Point2D (event.getSceneX(), event.getSceneY()));
                
                ClipboardContent content = new ClipboardContent();
                DragContainer container = new DragContainer();
                
                container.addData ("type", mDragOverIcon.getType().toString());
                content.put(DragContainer.AddNode, container);
                
                mDragOverIcon.startDragAndDrop (TransferMode.ANY).setContent(content);
                mDragOverIcon.setVisible(true);
                mDragOverIcon.setMouseTransparent(true);
                event.consume();
            }
        });
    }
    
    /**
    * @author Alex
    * Adds Drag detection to the drag nodes in the decrypt tab
    */
    private void addDecDragDetectionIcon(DragIcon dragIcon) {
        
        dragIcon.setOnDragDetected(new EventHandler <MouseEvent>() {
            
            @Override
            public void handle(MouseEvent event) {
                
                decbase_pane.setOnDragOver(mDecIconDragOverRoot);
                decrypt_pane.setOnDragOver(mDecIconDragOverLeftPane);
                decrypt_pane.setOnDragDropped(mDecIconDragDropped);
                
                DragIcon icn = (DragIcon) event.getSource();
                
                mDecDragOverIcon.setType(icn.getType());
                mDecDragOverIcon.relocateToPoint(new Point2D (event.getSceneX(), event.getSceneY()));
                
                ClipboardContent content = new ClipboardContent();
                DragContainer container = new DragContainer();
                
                container.addData ("type", mDecDragOverIcon.getType().toString());
                content.put(DragContainer.AddNode, container);
                
                mDecDragOverIcon.startDragAndDrop (TransferMode.ANY).setContent(content);
                mDecDragOverIcon.setVisible(true);
                mDecDragOverIcon.setMouseTransparent(true);
                event.consume();
            }
        });
    }
    
    /**
    * @author Alex
    * Adds Drag detection to the drag nodes in the decrypt tab
    */
    private void addKeyDragDetectionIcon(DragIcon dragIcon) {
        
        dragIcon.setOnDragDetected(new EventHandler <MouseEvent>() {
            
            @Override
            public void handle(MouseEvent event) {
                
                keybase_pane.setOnDragOver(mKeyIconDragOverRoot);
                key_pane.setOnDragOver(mKeyIconDragOverLeftPane);
                key_pane.setOnDragDropped(mKeyIconDragDropped);
                
                DragIcon icn = (DragIcon) event.getSource();
                
                mKeyDragOverIcon.setType(icn.getType());
                mKeyDragOverIcon.relocateToPoint(new Point2D (event.getSceneX(), event.getSceneY()));
                
                ClipboardContent content = new ClipboardContent();
                DragContainer container = new DragContainer();
                
                container.addData ("type", mKeyDragOverIcon.getType().toString());
                content.put(DragContainer.AddNode, container);
                
                mKeyDragOverIcon.startDragAndDrop (TransferMode.ANY).setContent(content);
                mKeyDragOverIcon.setVisible(true);
                mKeyDragOverIcon.setMouseTransparent(true);
                event.consume();
            }
        });
    }
    
    /**
    * @author Alex
    * Event Handlers for encrypt pane
    */    
    private void buildDragHandlers() {
        mIconDragOverRoot = new EventHandler<DragEvent>() {
            
            @Override
            public void handle (DragEvent event) {
                Point2D p = encrypt_pane.sceneToLocal(event.getSceneX(), event.getSceneY());
                
                if (!encrypt_pane.boundsInLocalProperty().get().contains(p)) {
                    mDragOverIcon.relocateToPoint(new Point2D(event.getSceneX() - 50, event.getSceneY() - 50));
                    return;
                }
                
                event.consume();
            }
        };
        
        mIconDragOverLeftPane = new EventHandler <DragEvent> () {

            @Override
            public void handle(DragEvent event) {

                event.acceptTransferModes(TransferMode.ANY);

                mDragOverIcon.relocateToPoint(
                    new Point2D(event.getSceneX() - 50, event.getSceneY() - 50)
                );

                event.consume();
            }
        };
        
        mIconDragDropped = new EventHandler <DragEvent> () {

            @Override
            public void handle(DragEvent event) {
                
                DragContainer container = 
                        (DragContainer) event.getDragboard().getContent(DragContainer.AddNode);
                
                container.addData("scene_coords", 
                        new Point2D(event.getSceneX(), event.getSceneY()));

                ClipboardContent content = new ClipboardContent();
                content.put(DragContainer.AddNode, container);

                event.getDragboard().setContent(content);
                event.setDropCompleted(true);
            }
        };
        
        this.setOnDragDone (new EventHandler <DragEvent> (){
            
            @Override
            public void handle (DragEvent event) {

                if (tabMode == tabType.encrypt) {
                    encrypt_pane.removeEventHandler(DragEvent.DRAG_OVER, mIconDragOverLeftPane);
                    encrypt_pane.removeEventHandler(DragEvent.DRAG_DROPPED, mIconDragDropped);
                    base_pane.removeEventHandler(DragEvent.DRAG_OVER, mIconDragOverRoot);

                    mDragOverIcon.setVisible(false);

                    DragContainer container = 
                            (DragContainer) event.getDragboard().getContent(DragContainer.AddNode);


                    if (container != null) {
                        if (container.getValue("scene_coords") != null) {
                            switch (DragNodeType.valueOf(container.getValue("type"))) {

                            case Start:
                                if (!startExists) {
                                    StartNode node = new StartNode();

                                    node.setType(DragNodeType.valueOf(container.getValue("type")));
                                    encrypt_pane.getChildren().add(node);


                                    Point2D cursorPoint = container.getValue("scene_coords");

                                    node.relocateToPoint(new Point2D(cursorPoint.getX()- 50, cursorPoint.getY() - 50));
                                    node.setParent(MainLayout.this);
                                    startExists = true;
                                }
                            break;

                            case pbox:
                                PboxNode pnode = new PboxNode();

                                pnode.setType(DragNodeType.valueOf(container.getValue("type")));
                                encrypt_pane.getChildren().add(pnode);

                                Point2D pcursorPoint = container.getValue("scene_coords");

                                pnode.relocateToPoint(new Point2D(pcursorPoint.getX()- 50, pcursorPoint.getY() - 50));
                                System.out.print(pnode);
                                pboxs.add(pnode);
                                pnode.setParent(MainLayout.this);
                                pnode.setId(idCounter);
                            break;

                            case sbox:
                                SboxNode snode = new SboxNode();

                                snode.setType(DragNodeType.valueOf(container.getValue("type")));
                                encrypt_pane.getChildren().add(snode);

                                Point2D scursorPoint = container.getValue("scene_coords");

                                snode.relocateToPoint(new Point2D(scursorPoint.getX()- 50, scursorPoint.getY() - 50));
                                sboxs.add(snode);
                                snode.setParent(MainLayout.this);
                                snode.setId(idCounter);
                            break;

                            case xor:
                                XorNode xnode = new XorNode();

                                xnode.setType(DragNodeType.valueOf(container.getValue("type")));
                                encrypt_pane.getChildren().add(xnode);

                                Point2D xcursorPoint = container.getValue("scene_coords");

                                xnode.relocateToPoint(new Point2D(xcursorPoint.getX()- 50, xcursorPoint.getY() - 50));
                                xors.add(xnode);
                                xnode.setParent(MainLayout.this);
                                xnode.setId(idCounter);
                            break;

                            case end:
                                if (!endExists) {
                                    EndNode enode = new EndNode();

                                    enode.setType(DragNodeType.valueOf(container.getValue("type")));
                                    encrypt_pane.getChildren().add(enode);

                                    Point2D ecursorPoint = container.getValue("scene_coords");

                                    enode.relocateToPoint(new Point2D(ecursorPoint.getX()- 50, ecursorPoint.getY() - 50));
                                    enode.setParent(MainLayout.this);
                                    endExists = true;
                                }
                            break;
                            
                            case key:
                                if (!eKeyExists) {
                                    Key knode = new Key();

                                    knode.setType(DragNodeType.valueOf(container.getValue("type")));
                                    encrypt_pane.getChildren().add(knode);

                                    Point2D ecursorPoint = container.getValue("scene_coords");

                                    knode.relocateToPoint(new Point2D(ecursorPoint.getX()- 50, ecursorPoint.getY() - 50));
                                    knode.setParent(MainLayout.this);
                                    knode.setId("ek");
                                    dKeyExists = true;
                                }
                            break;

                            default:
                                DragNode node1 = new DragNode();

                                node1.setUp();

                                node1.setType(DragNodeType.valueOf(container.getValue("type")));
                                encrypt_pane.getChildren().add(node1);

                                Point2D cursorPoint1 = container.getValue("scene_coords");

                                node1.relocateToPoint(new Point2D(cursorPoint1.getX()- 50, cursorPoint1.getY() - 50));

                            break;
                            }

                        }
                    }

                    container = (DragContainer) event.getDragboard().getContent(DragContainer.DragNode);

                    if (container != null) {
                        if (container.getValue("type") != null)
                            System.out.println("Moved node " + container.getValue("type"));
                    }

                    container = (DragContainer) event.getDragboard().getContent(DragContainer.AddLink);

                    if (container != null) {
                        String sourceId = container.getValue("source");
                        String targetId = container.getValue("target");

                        if (sourceId != null && targetId != null) {
                            System.out.println(container.getData());
                            NodeLink Link = new NodeLink();
                            Link.setParent(MainLayout.this);
                            Link.setId(idCounter);

                            encrypt_pane.getChildren().add(0, Link);

                            DragNode source = null;
                            DragNode target = null;

                            for (Node n: encrypt_pane.getChildren()) {
                                if (n.getId() == null)
                                    continue;
                                if (n.getId().equals(sourceId))
                                    source = (DragNode) n;
                                if (n.getId().equals(targetId))
                                    target = (DragNode) n;
                            }

                            if (source != null && target != null)
                                Link.bindEnds(source, target);

                            boolean linkExists = false;

                            for (int i = 0; i < connections.size() && !linkExists; i++) {
                                if (connections.get(i).getSourceId().equals(source.getId())) {
                                    if(connections.get(i).getTargetId().equals(target.getId())) {
                                        linkExists = true;
                                    }
                                }
                            }

                            if (source != null && target != null)
                                Link.bindEnds(source, target);

                            if (!linkExists) {

                                source.addConnection(Link);
                                target.addConnection(Link);
                                connections.add(Link);
                            }
                        }
                    }

                    event.consume();
                }
                else if (tabMode == tabType.decrypt) {
                    decrypt_pane.removeEventHandler(DragEvent.DRAG_OVER, mDecIconDragOverLeftPane);
                    decrypt_pane.removeEventHandler(DragEvent.DRAG_DROPPED, mDecIconDragDropped);
                    decbase_pane.removeEventHandler(DragEvent.DRAG_OVER, mDecIconDragOverRoot);

                    mDecDragOverIcon.setVisible(false);

                    DragContainer container = 
                            (DragContainer) event.getDragboard().getContent(DragContainer.AddNode);


                    if (container != null) {
                        if (container.getValue("scene_coords") != null) {
                            switch (DragNodeType.valueOf(container.getValue("type"))) {

                            case Start:
                                if (!decstartExists) {
                                    StartNode node = new StartNode();

                                    node.setType(DragNodeType.valueOf(container.getValue("type")));
                                    decrypt_pane.getChildren().add(node);


                                    Point2D cursorPoint = container.getValue("scene_coords");

                                    node.relocateToPoint(new Point2D(cursorPoint.getX()- 50, cursorPoint.getY() - 50));
                                    node.setParent(MainLayout.this);
                                    decstartExists = true;
                                }
                            break;

                            case pbox:
                                PboxNode pnode = new PboxNode();

                                pnode.setType(DragNodeType.valueOf(container.getValue("type")));
                                decrypt_pane.getChildren().add(pnode);

                                Point2D pcursorPoint = container.getValue("scene_coords");

                                pnode.relocateToPoint(new Point2D(pcursorPoint.getX()- 50, pcursorPoint.getY() - 50));
                                System.out.print(pnode);
                                decpboxs.add(pnode);
                                pnode.setParent(MainLayout.this);
                                pnode.setId(idCounter);
                            break;

                            case sbox:
                                SboxNode snode = new SboxNode();

                                snode.setType(DragNodeType.valueOf(container.getValue("type")));
                                decrypt_pane.getChildren().add(snode);

                                Point2D scursorPoint = container.getValue("scene_coords");

                                snode.relocateToPoint(new Point2D(scursorPoint.getX()- 50, scursorPoint.getY() - 50));
                                decsboxs.add(snode);
                                snode.setParent(MainLayout.this);
                                snode.setId(idCounter);
                            break;

                            case xor:
                                XorNode xnode = new XorNode();

                                xnode.setType(DragNodeType.valueOf(container.getValue("type")));
                                decrypt_pane.getChildren().add(xnode);

                                Point2D xcursorPoint = container.getValue("scene_coords");

                                xnode.relocateToPoint(new Point2D(xcursorPoint.getX()- 50, xcursorPoint.getY() - 50));
                                decxors.add(xnode);
                                xnode.setParent(MainLayout.this);
                                xnode.setId(idCounter);
                            break;

                            case end:
                                if (!decendExists) {
                                    EndNode enode = new EndNode();

                                    enode.setType(DragNodeType.valueOf(container.getValue("type")));
                                    decrypt_pane.getChildren().add(enode);

                                    Point2D ecursorPoint = container.getValue("scene_coords");

                                    enode.relocateToPoint(new Point2D(ecursorPoint.getX()- 50, ecursorPoint.getY() - 50));
                                    enode.setParent(MainLayout.this);
                                    decendExists = true;
                                }
                            break;
                            
                            case key:
                                if (!dKeyExists) {
                                    Key knode = new Key();

                                    knode.setType(DragNodeType.valueOf(container.getValue("type")));
                                    decrypt_pane.getChildren().add(knode);

                                    Point2D ecursorPoint = container.getValue("scene_coords");

                                    knode.relocateToPoint(new Point2D(ecursorPoint.getX()- 50, ecursorPoint.getY() - 50));
                                    knode.setParent(MainLayout.this);
                                    knode.setId("dk");
                                    dKeyExists = true;
                                }
                            break;

                            default:
                                DragNode node1 = new DragNode();

                                node1.setUp();

                                node1.setType(DragNodeType.valueOf(container.getValue("type")));
                                decrypt_pane.getChildren().add(node1);

                                Point2D cursorPoint1 = container.getValue("scene_coords");

                                node1.relocateToPoint(new Point2D(cursorPoint1.getX()- 50, cursorPoint1.getY() - 50));

                            break;
                            }

                        }       
                    }
                }
                else if (tabMode == tabType.key) {
                    key_pane.removeEventHandler(DragEvent.DRAG_OVER, mKeyIconDragOverLeftPane);
                    key_pane.removeEventHandler(DragEvent.DRAG_DROPPED, mKeyIconDragDropped);
                    key_pane.removeEventHandler(DragEvent.DRAG_OVER, mKeyIconDragOverRoot);

                    mKeyDragOverIcon.setVisible(false);

                    DragContainer container = 
                            (DragContainer) event.getDragboard().getContent(DragContainer.AddNode);


                    if (container != null) {
                        if (container.getValue("scene_coords") != null) {
                            switch (DragNodeType.valueOf(container.getValue("type"))) {

                            case Start:
                                if (!keystartExists) {
                                    StartNode node = new StartNode();

                                    node.setType(DragNodeType.valueOf(container.getValue("type")));
                                    key_pane.getChildren().add(node);


                                    Point2D cursorPoint = container.getValue("scene_coords");

                                    node.relocateToPoint(new Point2D(cursorPoint.getX()- 50, cursorPoint.getY() - 50));
                                    node.setParent(MainLayout.this);
                                    keystartExists = true;
                                }
                            break;

                            case pbox:
                                PboxNode pnode = new PboxNode();

                                pnode.setType(DragNodeType.valueOf(container.getValue("type")));
                                key_pane.getChildren().add(pnode);

                                Point2D pcursorPoint = container.getValue("scene_coords");

                                pnode.relocateToPoint(new Point2D(pcursorPoint.getX()- 50, pcursorPoint.getY() - 50));
                                System.out.print(pnode);
                                keypboxs.add(pnode);
                                pnode.setParent(MainLayout.this);
                                pnode.setId(idCounter);
                            break;

                            case sbox:
                                SboxNode snode = new SboxNode();

                                snode.setType(DragNodeType.valueOf(container.getValue("type")));
                                key_pane.getChildren().add(snode);

                                Point2D scursorPoint = container.getValue("scene_coords");

                                snode.relocateToPoint(new Point2D(scursorPoint.getX()- 50, scursorPoint.getY() - 50));
                                keysboxs.add(snode);
                                snode.setParent(MainLayout.this);
                                snode.setId(idCounter);
                            break;

                            case xor:
                                XorNode xnode = new XorNode();

                                xnode.setType(DragNodeType.valueOf(container.getValue("type")));
                                key_pane.getChildren().add(xnode);

                                Point2D xcursorPoint = container.getValue("scene_coords");

                                xnode.relocateToPoint(new Point2D(xcursorPoint.getX()- 50, xcursorPoint.getY() - 50));
                                keyxors.add(xnode);
                                xnode.setParent(MainLayout.this);
                                xnode.setId(idCounter);
                            break;

                            case subkey:
                                subKey knode = new subKey();

                                knode.setType(DragNodeType.valueOf(container.getValue("type")));
                                key_pane.getChildren().add(knode);

                                Point2D ecursorPoint = container.getValue("scene_coords");

                                knode.relocateToPoint(new Point2D(ecursorPoint.getX()- 50, ecursorPoint.getY() - 50));
                                knode.setParent(MainLayout.this);
                                subKeys.add(knode);
                                knode.setParentMain();
                                knode.setId(keyIdCounter);

                            break;

                            default:
                                DragNode node1 = new DragNode();

                                node1.setUp();

                                node1.setType(DragNodeType.valueOf(container.getValue("type")));
                                key_pane.getChildren().add(node1);

                                Point2D cursorPoint1 = container.getValue("scene_coords");

                                node1.relocateToPoint(new Point2D(cursorPoint1.getX()- 50, cursorPoint1.getY() - 50));

                            break;
                            }

                        }
                    }

                    container = (DragContainer) event.getDragboard().getContent(DragContainer.DragNode);

                    if (container != null) {
                        if (container.getValue("type") != null)
                            System.out.println("Moved node " + container.getValue("type"));
                    }

                    container = (DragContainer) event.getDragboard().getContent(DragContainer.AddLink);

                    if (container != null) {
                        String sourceId = container.getValue("source");
                        String targetId = container.getValue("target");

                        if (sourceId != null && targetId != null) {
                            System.out.println(container.getData());
                            NodeLink Link = new NodeLink();
                            Link.setParent(MainLayout.this);
                            Link.setId(idCounter);

                            key_pane.getChildren().add(0, Link);

                            DragNode source = null;
                            DragNode target = null;

                            for (Node n: key_pane.getChildren()) {
                                if (n.getId() == null)
                                    continue;
                                if (n.getId().equals(sourceId))
                                    source = (DragNode) n;
                                if (n.getId().equals(targetId))
                                    target = (DragNode) n;
                            }

                            if (source != null && target != null)
                                Link.bindEnds(source, target);

                            boolean linkExists = false;

                            for (int i = 0; i < keyconnections.size() && !linkExists; i++) {
                                if (keyconnections.get(i).getSourceId().equals(source.getId())) {
                                    if(keyconnections.get(i).getTargetId().equals(target.getId())) {
                                        linkExists = true;
                                    }
                                }
                            }

                            if (source != null && target != null)
                                Link.bindEnds(source, target);

                            if (!linkExists) {

                                source.addConnection(Link);
                                target.addConnection(Link);
                                keyconnections.add(Link);
                            }
                        }
                    }

                    event.consume();
                }
            }
        });
        
        encrypt_pane.setOnMouseClicked(new EventHandler <MouseEvent> (){
            
            @Override
            public void handle (MouseEvent event) {
                System.out.print(new Point2D(event.getX(), event.getY()));
                event.consume();
            }
            
        });
    }
    
    /**
    * @author Alex
    * Event Handlers for decrypt pane
    */    
    private void buildDecDragHandlers() {
        mDecIconDragOverRoot = new EventHandler<DragEvent>() {
            
            @Override
            public void handle (DragEvent event) {
                Point2D p = decrypt_pane.sceneToLocal(event.getSceneX(), event.getSceneY());
                
                if (!decrypt_pane.boundsInLocalProperty().get().contains(p)) {
                    mDecDragOverIcon.relocateToPoint(new Point2D(event.getSceneX() - 50, event.getSceneY() - 50));
                    return;
                }
                
                event.consume();
            }
        };
        
        mDecIconDragOverLeftPane = new EventHandler <DragEvent> () {

            @Override
            public void handle(DragEvent event) {

                event.acceptTransferModes(TransferMode.ANY);

                mDecDragOverIcon.relocateToPoint(
                    new Point2D(event.getSceneX() - 50, event.getSceneY() - 50)
                );

                event.consume();
            }
        };
        
        mDecIconDragDropped = new EventHandler <DragEvent> () {

            @Override
            public void handle(DragEvent event) {
                
                DragContainer container = 
                        (DragContainer) event.getDragboard().getContent(DragContainer.AddNode);
                
                container.addData("scene_coords", 
                        new Point2D(event.getSceneX(), event.getSceneY()));

                ClipboardContent content = new ClipboardContent();
                content.put(DragContainer.AddNode, container);

                event.getDragboard().setContent(content);
                event.setDropCompleted(true);
            }
        };
        
        
        
        decrypt_pane.setOnMouseClicked(new EventHandler <MouseEvent> (){
            
            @Override
            public void handle (MouseEvent event) {
                System.out.print(new Point2D(event.getX(), event.getY()));
                event.consume();
            }
            
        });
    }
    
    private void buildKeyDragHandlers() {
        mKeyIconDragOverRoot = new EventHandler<DragEvent>() {
            
            @Override
            public void handle (DragEvent event) {
                Point2D p = key_pane.sceneToLocal(event.getSceneX(), event.getSceneY());
                
                if (!key_pane.boundsInLocalProperty().get().contains(p)) {
                    mKeyDragOverIcon.relocateToPoint(new Point2D(event.getSceneX() - 50, event.getSceneY() - 50));
                    return;
                }
                
                event.consume();
            }
        };
        
        mKeyIconDragOverLeftPane = new EventHandler <DragEvent> () {

            @Override
            public void handle(DragEvent event) {

                event.acceptTransferModes(TransferMode.ANY);

                mKeyDragOverIcon.relocateToPoint(
                    new Point2D(event.getSceneX() - 50, event.getSceneY() - 50)
                );

                event.consume();
            }
        };
        
        mKeyIconDragDropped = new EventHandler <DragEvent> () {

            @Override
            public void handle(DragEvent event) {
                
                DragContainer container = 
                        (DragContainer) event.getDragboard().getContent(DragContainer.AddNode);
                
                container.addData("scene_coords", 
                        new Point2D(event.getSceneX(), event.getSceneY()));

                ClipboardContent content = new ClipboardContent();
                content.put(DragContainer.AddNode, container);

                event.getDragboard().setContent(content);
                event.setDropCompleted(true);
            }
        };
        
        
        
        key_pane.setOnMouseClicked(new EventHandler <MouseEvent> (){
            
            @Override
            public void handle (MouseEvent event) {
                System.out.print(new Point2D(event.getX(), event.getY()));
                event.consume();
            }
            
        });
    }
    
    /**
    * @author Alex
    */    
    public void updateConnections(String id) {
        for (int i=0; i<connections.size(); i++) {
	    if ( connections.get(i).getId().equals(id) ) {
                String sId = connections.get(i).getSourceId();
                String tId = connections.get(i).getTargetId();
                for (int j=0; j<pboxs.size(); j++) {
                    if(pboxs.get(j).getId().equals(sId))
                        pboxs.get(j).removeConnection(id);
                    if(pboxs.get(j).getId().equals(tId))
                        pboxs.get(j).removeConnection(id);
                }
                for (int j=0; j<sboxs.size(); j++) {
                    if(sboxs.get(j).getId().equals(sId))
                        sboxs.get(j).removeConnection(id);
                    if(sboxs.get(j).getId().equals(tId))
                        sboxs.get(j).removeConnection(id);
                }
                for (int j=0; j<xors.size(); j++) {
                    if(xors.get(j).getId().equals(sId))
                        xors.get(j).removeConnection(id);
                    if(xors.get(j).getId().equals(tId))
                        xors.get(j).removeConnection(id);
                }
		connections.remove(i);
		return;
	    }
	}
        for (int i=0; i<decconnections.size(); i++) {
	    if ( decconnections.get(i).getId().equals(id) ) {
                String sId = decconnections.get(i).getSourceId();
                String tId = decconnections.get(i).getTargetId();
                for (int j=0; j<decpboxs.size(); j++) {
                    if(decpboxs.get(j).getId().equals(sId))
                        decpboxs.get(j).removeConnection(id);
                    if(decpboxs.get(j).getId().equals(tId))
                        decpboxs.get(j).removeConnection(id);
                }
                for (int j=0; j<decsboxs.size(); j++) {
                    if(decsboxs.get(j).getId().equals(sId))
                        decsboxs.get(j).removeConnection(id);
                    if(decsboxs.get(j).getId().equals(tId))
                        decsboxs.get(j).removeConnection(id);
                }
                for (int j=0; j<decxors.size(); j++) {
                    if(decxors.get(j).getId().equals(sId))
                        decxors.get(j).removeConnection(id);
                    if(decxors.get(j).getId().equals(tId))
                        decxors.get(j).removeConnection(id);
                }
		decconnections.remove(i);
		return;
	    }
	}
        for (int i=0; i<keyconnections.size(); i++) {
	    if ( keyconnections.get(i).getId().equals(id) ) {
                String sId = keyconnections.get(i).getSourceId();
                String tId = keyconnections.get(i).getTargetId();
                for (int j=0; j<keypboxs.size(); j++) {
                    if(keypboxs.get(j).getId().equals(sId))
                        keypboxs.get(j).removeConnection(id);
                    if(keypboxs.get(j).getId().equals(tId))
                        keypboxs.get(j).removeConnection(id);
                }
                for (int j=0; j<keysboxs.size(); j++) {
                    if(keysboxs.get(j).getId().equals(sId))
                        keysboxs.get(j).removeConnection(id);
                    if(keysboxs.get(j).getId().equals(tId))
                        keysboxs.get(j).removeConnection(id);
                }
                for (int j=0; j<keyxors.size(); j++) {
                    if(keyxors.get(j).getId().equals(sId))
                        keyxors.get(j).removeConnection(id);
                    if(keyxors.get(j).getId().equals(tId))
                        keyxors.get(j).removeConnection(id);
                }
                for (int j=0; j<subKeys.size(); j++) {
                    if(subKeys.get(j).getId().equals(sId))
                        subKeys.get(j).removeConnection(id);
                    if(subKeys.get(j).getId().equals(tId))
                        subKeys.get(j).removeConnection(id);
                }
		keyconnections.remove(i);
		return;
	    }
	}
    }
    
    /**
     * @author Nick
     */
    public void runConfirm() throws IOException {
        
	SaveLoadTool saver = new SaveLoadTool();
	
	saver.AddPBoxs("encrypt", pboxs);
	saver.AddSBoxes("encrypt", sboxs);
	saver.AddXors("encrypt", xors);
	saver.AddConnections("encrypt", connections);
	saver.AddProperties("encrypt");
	
	saver.AddPBoxs("decrypt", pboxs);
	saver.AddSBoxes("decrypt", sboxs);
	saver.AddXors("decrypt", xors);
	saver.AddConnections("decrypt", connections);
	saver.AddProperties("decrypt");
	
	saver.AddPBoxs("keygen", pboxs);
	saver.AddSBoxes("keygen", sboxs);
	saver.AddXors("keygen", xors);
	saver.AddConnections("keygen", connections);
	
	saver.AddProperties(properties);
	//saver.AddProperties(numRounds.getText(), blockSize.getText(), keySize.getText(), "counter", "zero padding", "0", "0");
	
	
	
        //pass in the lists into a conversion function then store them in cipherwrapper
        //assign conversion function returned lists to 
        
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/resources/runConfirm.fxml"));
        RunConfirm confirm = new RunConfirm(saver);         //create runconfirm controller objet
        fxmlLoader.setController(confirm);
        Parent root = fxmlLoader.load();
        Stage stage = new Stage();
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.setOpacity(1);
        stage.setTitle("Encrypt or Decrypt");
        stage.setScene(new Scene(root, 620, 400));
        stage.showAndWait();
    }
    
    /**
    * @author Alex
    */    
    public void listpboxes() {
        for (int i = 0; i < pboxs.size(); i++) {
            System.out.println(pboxs.get(i).getCoords());
        }
        for (int i = 0; i < connections.size(); i++) {
            System.out.println(connections.get(i).getSourceId());
        }
    }
    
    
    /**
    * @author Alex
    */    
    @FXML
    public void switchTab() {
        if (encrypt_tab.isSelected())
            tabMode = tabType.encrypt;
        else if (decrypt_tab.isSelected())
            tabMode = tabType.decrypt;
        else if (key_tab.isSelected())
            tabMode = tabType.key;
        System.out.println(tabMode);
    }
    
}
