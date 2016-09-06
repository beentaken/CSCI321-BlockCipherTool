/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

/**
 *
 * @author Aloe2020
 */import java.io.IOException;

import javafx.event.EventHandler;
import javafx.event.EventType;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Point2D;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.SplitPane;
import javafx.scene.input.ClipboardContent;
import javafx.scene.input.DragEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.TransferMode;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;

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
        //Add one icon that will be used for the drag-drop process
        //This is added as a child to the root AnchorPane so it can be 
        //visible on both sides of the split pane.
        mDragOverIcon = new DragIcon();

        mDragOverIcon.setVisible(false);
        mDragOverIcon.setOpacity(0.65);
        getChildren().add(mDragOverIcon);  

        //populate left pane with multiple colored icons for testing
        for (int i = 0; i < 7; i++) {

            DragIcon icn = new DragIcon();
            
            addDragDetectionIcon(icn);

            icn.setType(DragNodeType.values()[i]);
            node_list.getChildren().add(icn);
        }
        
        buildDragHandlers();
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
    
    private void addDragDetection(DragNode dragNode) {
        
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
    }
    
    private void buildDragHandlers() {
        mIconDragOverRoot = new EventHandler<DragEvent>() {
            
            @Override
            public void handle (DragEvent event) {
                Point2D p = main_window.sceneToLocal(event.getSceneX(), event.getSceneY());
                
                if (!main_window.boundsInLocalProperty().get().contains(p)) {
                    mDragOverIcon.relocateToPoint(new Point2D(event.getSceneX(), event.getSceneY()));
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
                    new Point2D(event.getSceneX(), event.getSceneY())
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
                        DragNode node = new DragNode();
                        
                        node.setType(DragNodeType.valueOf(container.getValue("type")));
                        main_window.getChildren().add(node);
                        
                        Point2D cursorPoint = container.getValue("scene_coords");
                        
                        node.relocateToPoint(new Point2D(cursorPoint.getX()- 32, cursorPoint.getY() - 32));
                    }
                }
                
                container = (DragContainer) event.getDragboard().getContent(DragContainer.DragNode);
                
                if (container != null) {
                    if (container.getValue("type") != null)
                        System.out.println("Moved node " + container.getValue("type"));
                }
                
                container = (DragContainer) event.getDragboard().getContent(DragContainer.AddLink);
                
                if (container != null) {
                    System.out.println(container.getData());
                }

                event.consume();
            }
        });
    }
    
}
