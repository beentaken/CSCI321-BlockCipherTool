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
/**
 *
 * @author Aloe2020
 */import java.io.IOException;
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
import javafx.scene.layout.BorderPane;

/**
 *
 * @author Aloe2020
 */
public class MainLayout extends AnchorPane{
    
    @FXML SplitPane base_pane;
    @FXML AnchorPane main_window;
    @FXML VBox node_list;
    
    private DragIcon mDragOverIcon = null;
    
    private EventHandler<DragEvent> mIconDragOverRoot=null;
    private EventHandler<DragEvent> mIconDragDropped=null;
    private EventHandler<DragEvent> mIconDragOverLeftPane=null;
    
    private List<PboxNode> pboxs;
    private List<SboxNode> sboxs;
    //private List<CipherFunctionWrapper> functions;
    private List<XorNode> xors;
    private List<NodeLink> connections;
    private PropertiesWrapper properties;
    
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
    }

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

        //populate left pane with multiple colored icons for testing
        for (int i = 0; i < 5; i++) {

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
                    
            }
            
            node_list.getChildren().add(icn);
        }
        
        
        buildDragHandlers();
        
        pboxs = new ArrayList<PboxNode>();
        sboxs = new ArrayList<SboxNode>();
        xors = new ArrayList<XorNode>();
        connections = new ArrayList<NodeLink>();
        properties = new PropertiesWrapper();
    }
    
    private void addDragDetectionIcon(DragIcon dragIcon) {
        
        dragIcon.setOnDragDetected(new EventHandler <MouseEvent>() {
            
            @Override
            public void handle(MouseEvent event) {
                
                base_pane.setOnDragOver(mIconDragOverRoot);
                main_window.setOnDragOver(mIconDragOverLeftPane);
                main_window.setOnDragDropped(mIconDragDropped);
                
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
    
    /*private void addDragDetection(DragNode dragNode) {
        
        dragNode.setOnDragDetected(new EventHandler <MouseEvent> () {
            
            @Override
            public void handle(MouseEvent event) {
                
                base_pane.setOnDragOver(mIconDragOverRoot);
                main_window.setOnDragOver(mIconDragOverLeftPane);
                main_window.setOnDragDropped(mIconDragDropped);
                
                DragNode nde = (DragNode) event.getSource();
                
                mDragOverIcon.setType(nde.getType());
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
    }*/
    
    private void buildDragHandlers() {
        mIconDragOverRoot = new EventHandler<DragEvent>() {
            
            @Override
            public void handle (DragEvent event) {
                Point2D p = main_window.sceneToLocal(event.getSceneX(), event.getSceneY());
                
                if (!main_window.boundsInLocalProperty().get().contains(p)) {
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

                main_window.removeEventHandler(DragEvent.DRAG_OVER, mIconDragOverLeftPane);
                main_window.removeEventHandler(DragEvent.DRAG_DROPPED, mIconDragDropped);
                base_pane.removeEventHandler(DragEvent.DRAG_OVER, mIconDragOverRoot);

                mDragOverIcon.setVisible(false);
                
                DragContainer container = 
                        (DragContainer) event.getDragboard().getContent(DragContainer.AddNode);
                
                
                if (container != null) {
                    if (container.getValue("scene_coords") != null) {
                        switch (DragNodeType.valueOf(container.getValue("type"))) {
                        
                        case Start:
                            StartNode node = new StartNode();

                            node.setType(DragNodeType.valueOf(container.getValue("type")));
                            main_window.getChildren().add(node);
                            

                            Point2D cursorPoint = container.getValue("scene_coords");

                            node.relocateToPoint(new Point2D(cursorPoint.getX()- 50, cursorPoint.getY() - 50));
                        break;
                        
                        case pbox:
                            PboxNode pnode = new PboxNode();

                            pnode.setType(DragNodeType.valueOf(container.getValue("type")));
                            main_window.getChildren().add(pnode);

                            Point2D pcursorPoint = container.getValue("scene_coords");

                            pnode.relocateToPoint(new Point2D(pcursorPoint.getX()- 50, pcursorPoint.getY() - 50));
                            System.out.print(pnode);
                            pboxs.add(pnode);
                            pnode.setParent(MainLayout.this);
                        break;
                        
                        case sbox:
                            SboxNode snode = new SboxNode();

                            snode.setType(DragNodeType.valueOf(container.getValue("type")));
                            main_window.getChildren().add(snode);

                            Point2D scursorPoint = container.getValue("scene_coords");

                            snode.relocateToPoint(new Point2D(scursorPoint.getX()- 50, scursorPoint.getY() - 50));
                            sboxs.add(snode);
                        break;
                        
                        case xor:
                            XorNode xnode = new XorNode();

                            xnode.setType(DragNodeType.valueOf(container.getValue("type")));
                            main_window.getChildren().add(xnode);

                            Point2D xcursorPoint = container.getValue("scene_coords");

                            xnode.relocateToPoint(new Point2D(xcursorPoint.getX()- 50, xcursorPoint.getY() - 50));
                            xors.add(xnode);
                        break;
                        
                        case end:
                            EndNode enode = new EndNode();

                            enode.setType(DragNodeType.valueOf(container.getValue("type")));
                            main_window.getChildren().add(enode);

                            Point2D ecursorPoint = container.getValue("scene_coords");

                            enode.relocateToPoint(new Point2D(ecursorPoint.getX()- 50, ecursorPoint.getY() - 50));
                        break;
                        
                        default:
                            DragNode node1 = new DragNode();
                            
                            node1.setUp();

                            node1.setType(DragNodeType.valueOf(container.getValue("type")));
                            main_window.getChildren().add(node1);

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
                        
                        main_window.getChildren().add(0, Link);
                        
                        DragNode source = null;
                        DragNode target = null;
                        
                        for (Node n: main_window.getChildren()) {
                            if (n.getId() == null)
                                continue;
                            if (n.getId().equals(sourceId))
                                source = (DragNode) n;
                            if (n.getId().equals(targetId))
                                target = (DragNode) n;
                        }
                        
                        if (source != null && target != null)
                            Link.bindEnds(source, target);
                        
			source.addConnection(Link);
			target.addConnection(Link);
                        connections.add(Link);
                    }
                }

                event.consume();
            }
        });
        
        main_window.setOnMouseClicked(new EventHandler <MouseEvent> (){
            
            @Override
            public void handle (MouseEvent event) {
                System.out.print(new Point2D(event.getX(), event.getY()));
                event.consume();
            }
            
        });
    }
    
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
		connections.remove(i);
		return;
	    }
	}
    }
    
    public void runConfirm() throws IOException {
        
        CipherWrapper cWrap = new CipherWrapper();
        //pass in the lists into a conversion function then store them in cipherwrapper
        //assign conversion function returned lists to 
        
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/resources/runConfirm.fxml"));
        RunConfirm confirm = new RunConfirm(cWrap);         //create runconfirm controller objet
        fxmlLoader.setController(confirm);
        Parent root = fxmlLoader.load();
        Stage stage = new Stage();
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.setOpacity(1);
        stage.setTitle("Encrypt or Decrypt");
        stage.setScene(new Scene(root, 620, 400));
        stage.showAndWait();
    }
    
    public void listpboxes() {
        for (int i = 0; i < pboxs.size(); i++) {
            System.out.println(pboxs.get(i).getCoords());
        }
        for (int i = 0; i < connections.size(); i++) {
            System.out.println(connections.get(i).getSourceId());
        }
    }
    
}
