/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import java.io.IOException;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;

import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Point2D;
import javafx.scene.control.Label;
import javafx.scene.input.ClipboardContent;
import javafx.scene.input.DataFormat;
import javafx.scene.input.DragEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.TransferMode;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;

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
    
    public DragNode() {

        FXMLLoader fxmlLoader = new FXMLLoader(
            getClass().getResource("/resources/DragNode.fxml")
        );

        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);
        
        self = this;

        try {
            fxmlLoader.load();

        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
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
    
    public void relocateToPoint (Point2D p) {
        Point2D localCoords = getParent().sceneToLocal(p);

        relocate ( 
            (int) (localCoords.getX() - mDragOffset.getX()),
            (int) (localCoords.getY() - mDragOffset.getY())
        );
        System.out.println("x, y: " + localCoords.getX() + ", " + localCoords.getY());
    }
    
    public DragNodeType getType() { return mType;}
    
    public void setType(DragNodeType type) {

        mType = type;
        
        getStyleClass().clear();
        getStyleClass().add("dragnode");

        switch (mType) {

        case blue:
        getStyleClass().add("node-blue");
        break;

        case red:
        getStyleClass().add("node-red");            
        break;

        case green:
        getStyleClass().add("node-green");
        break;

        case grey:
        getStyleClass().add("node-grey");
        break;

        case purple:
        getStyleClass().add("node-purple");
        break;

        case yellow:
        getStyleClass().add("node-yellow");
        break;

        case black:
        getStyleClass().add("node-black");
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
                
                container.addData("source", getType().toString());
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
                DragNode parent = (DragNode) link_handle.getParent().getParent().getParent();
                
                ClipboardContent content = new ClipboardContent();
                
                container.addData("target", parent.getType().toString());
                
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
                
                mDragLink.setEnd(new Point2D(event.getX(), event.getY()));
                
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