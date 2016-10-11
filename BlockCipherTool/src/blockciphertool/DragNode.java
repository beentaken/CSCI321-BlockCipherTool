/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import blockciphertool.wrappers.input;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.ListIterator;
import java.util.UUID;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;

import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Point2D;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.input.ClipboardContent;
import javafx.scene.input.DataFormat;
import javafx.scene.input.DragEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.TransferMode;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;

/**
 *
 * @author Aloe2020
 */
public class DragNode extends AnchorPane{
    
    @FXML AnchorPane root_pane;
    @FXML AnchorPane left_link_handle;
    @FXML AnchorPane right_link_handle;
    @FXML AnchorPane top_link_handle;
    @FXML AnchorPane bottom_link_handle;
    
    private EventHandler mContextDragOver;
    private EventHandler mContextDragDropped;
    
    private EventHandler <MouseEvent> mLinkHandleDragDetected;
    private EventHandler <DragEvent> mLinkHandleDragDropped;
    private EventHandler <DragEvent> mContextLinkDragOver;
    private EventHandler <DragEvent> mContextLinkDragDropped;
    
    private DragNodeType mType = null;
    
    private Point2D mDragOffset = new Point2D(0.0, 0.0);
    
    @FXML private AnchorPane drag_zone;
    @FXML private Label title_bar;
    @FXML private Label close_button;
    
    private final DragNode self;
    
    private NodeLink mDragLink = null;
    private AnchorPane parent_pane = null;
    
    private List <String> mLinkIds = new ArrayList <String> ();
    
    private List<NodeLink> connections = new ArrayList<NodeLink> ();
    
    private int xCoord;
    private int yCoord;
    
    public DragNode() {
        /**
         * Copy whatever is commented in this constructor to the inherited node class, 
         * except change the getResources to that node's FXML file location
         */
        /*
        /*FXMLLoader fxmlLoader = new FXMLLoader(
            getClass().getResource("/resources/DragNode.fxml")
        );

        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);
        */
        self = this;
        /*
        try {
            fxmlLoader.load();

        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
        */
        setId(UUID.randomUUID().toString());
    }
    
    public void setUp() {
        /**
         * Copy whatever is commented in this constructor to the inherited node class, 
         * except change the getResources to that node's FXML file location
         */
        
        FXMLLoader fxmlLoader = new FXMLLoader(
            getClass().getResource("/resources/DragNode.fxml")
        );

        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);
        
        //self = this;
        
        try {
            fxmlLoader.load();

        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
        
        setId(UUID.randomUUID().toString());
    }
    

    @FXML
    private void initialize() {
        buildNodeDragHandlers();
        buildLinkDragHandlers();
        
        left_link_handle.setOnDragDetected(mLinkHandleDragDetected);
        right_link_handle.setOnDragDetected(mLinkHandleDragDetected);
        top_link_handle.setOnDragDetected(mLinkHandleDragDetected);
        bottom_link_handle.setOnDragDetected(mLinkHandleDragDetected);
        
        left_link_handle.setOnDragDropped(mLinkHandleDragDropped);
        right_link_handle.setOnDragDropped(mLinkHandleDragDropped);
        top_link_handle.setOnDragDropped(mLinkHandleDragDropped);
        bottom_link_handle.setOnDragDropped(mLinkHandleDragDropped);
        
        mDragLink = new NodeLink();
        mDragLink.setVisible(false);
        
        parentProperty().addListener(new ChangeListener() {
            
            @Override
            public void changed(ObservableValue observable, Object oldValue, Object newValue){
                parent_pane = (AnchorPane) getParent();
            }
        });
    }
    
    public void registerLink(String linkId) {
        mLinkIds.add(linkId);
    }
    
    public String GetLink(int index) {
        String linkId = mLinkIds.get(index);
        return linkId;
    }
    
    public List<String> getLinks() {
	return mLinkIds;
    }
    
    public void addConnection(NodeLink connection) {
	connections.add(connection);
    }
    
    public List<NodeLink> getConnections() {
	return this.connections;
    }
    
    public void removeConnection(String id ) {
	boolean found = false;
	for (int i=0; i<connections.size(); i++) {
	    if ( connections.get(i).getId().equals(id) ) {
		connections.remove(i);
		return;
	    }
	}
	System.out.println("err: connection not found");
    }
    
    
    public List<input> GetLinkList() {
        List<input> inputs = null;
        for(int i = 0; i < mLinkIds.size(); i++) {
            input temp = new input();
            temp.setConnectorID(mLinkIds.get(i));
            //temp.setSize(mLinkIds);
            //size is to be implemented later
            inputs.add(i, temp);
        }
        return inputs;
    }
    
    public void relocateToPoint (Point2D p) {
        Point2D localCoords = getParent().sceneToLocal(p);

        relocate ( 
            (int) (localCoords.getX() - mDragOffset.getX()),
            (int) (localCoords.getY() - mDragOffset.getY())
        );
        
        setCoords(localCoords);
        
        System.out.println("x, y: " + (localCoords.getX() - mDragOffset.getX()) + ", " + (localCoords.getY() - mDragOffset.getY()));
    }
    
    public void setCoords (Point2D p) {
        xCoord = (int) (p.getX() - mDragOffset.getX());
        yCoord = (int) (p.getY() - mDragOffset.getY());
    }
    
    public void setCoords (String xString, String yString) {
        xCoord = Integer.parseInt(xString);
        yCoord = Integer.parseInt(yString);
    }
    
    public Point2D getCoords() {
        Point2D p = new Point2D(xCoord, yCoord);
        return p;
    }
    
    public String getXString() {
        String xString = "" + xCoord;
        return xString;
    }
    
    public String getYString() {
        String yString = "" + yCoord;
        return yString;
    }
    
    public String getNodeID() {
        return getId();
    }
    
    public void setNodeID(String myId) {
        setId(myId);
    }
    
    public DragNodeType getType() { return mType;}
    
    public void setType(DragNodeType type) {

        mType = type;
        
        getStyleClass().clear();
        getStyleClass().add("dragnode");

        switch (mType) {

        case pbox:
        getStyleClass().add("node-pbox");
        break;

        case sbox:
        getStyleClass().add("node-sbox");            
        break;
        
        case Start:
        getStyleClass().add("node-start");
        break;

        case xor:
        getStyleClass().add("node-xor");
        break;

        case end:
        getStyleClass().add("node-end");
        break;
        

        default:
        break;
        }
    }
    
    public void buildNodeDragHandlers() {
        
        mContextDragOver = new EventHandler <DragEvent>() {

            @Override
            public void handle(DragEvent event) {		

                event.acceptTransferModes(TransferMode.ANY);				
                relocateToPoint(new Point2D( event.getSceneX(), event.getSceneY()));

                event.consume();
            }
        };

        //dragdrop for node dragging
        mContextDragDropped = new EventHandler <DragEvent> () {

            @Override
            public void handle(DragEvent event) {

                getParent().setOnDragOver(null);
                getParent().setOnDragDropped(null);

                event.setDropCompleted(true);

                event.consume();
            }
        };
        //close button click
        close_button.setOnMouseClicked( new EventHandler <MouseEvent> () {

            @Override
            public void handle(MouseEvent event) {
                AnchorPane parent  = (AnchorPane) self.getParent();
                parent.getChildren().remove(self);
                
                for (ListIterator <String> iterId = mLinkIds.listIterator(); iterId.hasNext();) {
                    String id = iterId.next();
                    
                    for (ListIterator <Node> iterNode = parent.getChildren().listIterator(); iterNode.hasNext();) {
                        Node node = iterNode.next();
                        
                        if (node.getId() == null)
                            continue;
                        if (node.getId().equals(id))
                            iterNode.remove();
                    }
                }
            }

        });
        
        drag_zone.setOnDragDetected(new EventHandler<MouseEvent>() {
            
            @Override
            public void handle(MouseEvent event) {
                getParent().setOnDragOver(null);
                getParent().setOnDragDropped(null);
                
                getParent().setOnDragOver(mContextDragOver);
                getParent().setOnDragDropped(mContextDragDropped);
                
                
                mDragOffset = new Point2D(event.getX() + 10, event.getY() + 15);
                //System.out.println("x, y: " + event.getX() + ", " + event.getY());
                relocateToPoint(new Point2D(event.getSceneX(), event.getSceneY()));
                //System.out.println("x, y: " + event.getSceneX() + ", " + event.getSceneY());
                
                ClipboardContent content = new ClipboardContent();
                DragContainer container = new DragContainer();
                
                container.addData("type", mType.toString());
                content.put(DragContainer.DragNode, container);
                
                startDragAndDrop(TransferMode.ANY).setContent(content);
                
                event.consume();
            }
        });
    }
    
    private void buildLinkDragHandlers() {
        
        mLinkHandleDragDetected = new EventHandler <MouseEvent> () {
            
            @Override
            public void handle(MouseEvent event) {
                
                getParent().setOnDragOver(null);
                getParent().setOnDragDropped(null);
                
                getParent().setOnDragOver(mContextLinkDragOver);
                getParent().setOnDragDropped(mContextLinkDragDropped);
                
                parent_pane.getChildren().add(0, mDragLink);
                
                mDragLink.setVisible(false);
                
                Point2D p = new Point2D(
                        getLayoutX() - 100,
                        getLayoutY() + 17);
                
                
                
                mDragLink.setStart(p);
                
                
                Point2D localCoords = getParent().localToParent(p);  
                System.out.println("Parent coords x, " + localCoords.getX() + ", y: " + localCoords.getY());
                System.out.println("Parent x, " + p.getX() + ", y: " + p.getY());
                System.out.println("Layout x, " + (getLayoutX() - event.getX()) + ", y: " + (getLayoutY() - event.getY()));
                
                ClipboardContent content = new ClipboardContent();
                DragContainer container = new DragContainer();
                
                container.addData("source", getId());
                content.put(DragContainer.AddLink, container);
                
                startDragAndDrop(TransferMode.ANY).setContent(content);
                
                event.consume();
            }
        };
        
        mLinkHandleDragDropped = new EventHandler<DragEvent>() {
            @Override
            public void handle(DragEvent event) {
                getParent().setOnDragOver(null);
                getParent().setOnDragDropped(null);
                
                DragContainer container = (DragContainer) event.getDragboard().getContent(DragContainer.AddLink);
                
                if (container == null)
                    return;
                
                mDragLink.setVisible(false);
                parent_pane.getChildren().remove(0);
                
                AnchorPane link_handle = (AnchorPane) event.getSource();
                //DragNode parent = (DragNode) link_handle.getParent().getParent().getParent();
                
                ClipboardContent content = new ClipboardContent();
                
                container.addData("target", getId());
                
                content.put(DragContainer.AddLink, container);
                
                event.getDragboard().setContent(content);
                event.setDropCompleted(true);
                event.consume();
            }
        };
        
        mContextLinkDragOver = new EventHandler<DragEvent>() {
            @Override
            public void handle(DragEvent event) {
                event.acceptTransferModes(TransferMode.ANY);
                
                if(!mDragLink.isVisible())
                    mDragLink.setVisible(true);
                
                mDragLink.setEnd(new Point2D(event.getX() - 150, event.getY() - 33));
                
                event.consume();
            }
        };
        
        mContextLinkDragDropped = new EventHandler<DragEvent>() {
            @Override
            public void handle(DragEvent event) {
                getParent().setOnDragOver(null);
                getParent().setOnDragDropped(null);
                
                mDragLink.setVisible(false);
                parent_pane.getChildren().remove(0);
                
                event.setDropCompleted(true);
                event.consume();
            }
        };
    }
    
    
}