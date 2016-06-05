import vtk
import sys
import PyQt4
from PyQt4 import Qt
from PyQt4 import QtGui as gui
from PyQt4 import QtCore as qcore
from vtk.qt4.QVTKRenderWindowInteractor import QVTKRenderWindowInteractor 
import swctree as stree
import Mostd as MD
import cv2 as cv
import numpy as np
import os, time
from threading import Thread
import multiprocessing
import time
import math
import re


class MyActor(vtk.vtkActor):
    def __init__(self):
        self.maFieldData = vtk.vtkFieldData()

class ChoooseNLineWidget(gui.QWidget):
    def __init__(self, n):
        super(ChoooseNLineWidget, self).__init__()
        self.layout = gui.QHBoxLayout(self)
        self.setLayout(self.layout)
        self.label1 = gui.QLabel(self)
        self.label1.setText('Line')
        self.spinBox = gui.QSpinBox(self)
        self.spinBox.setMaximum(n)
        self.spinBox.setMinimum(1)
#         self.label2 = gui.QLabel(self)
#         self.label2txt = 'of ' + '%d'%n
#         self.label2.setText(self.label2txt)
        self.layout.addWidget(self.label1)
        self.layout.addWidget(self.spinBox)
#         self.layout.addWidget(self.label2)
#         self.button1 = gui.QPushButton(text='Show', parent=self)


class BouttonInteractorStyle(vtk.vtkInteractorStyleImage):
    def __init__(self):
        self.AddObserver('LeftButtonPressEvent', self.leftButtonPressEvent)
        self.AddObserver('MouseWheelForwardEvent', self.sliceForward)
        self.AddObserver('MouseWheelBackwardEvent', self.sliceBackward)
        
    def leftButtonPressEvent(self, obj, e):
        global main_win
        if main_win.toolBarAction_choose.isChecked():
            x, y = self.GetInteractor().GetEventPosition()
            main_win.actorPicker.Pick(x, y, 0, main_win.ren1)
            actor_1 = main_win.actorPicker.GetActor()
            if actor_1 and (main_win.pickedActor != actor_1):
                if main_win.pickedActor:
                    main_win.pickedActor.GetProperty().SetColor(1.0, 0.0, 1.0)
                main_win.pickedActor = actor_1
                main_win.pickedActor.GetProperty().SetColor(0.0, 1.0, 0.0)
                main_win.vtk_widget.Render()
        else:
            x, y = self.GetInteractor().GetEventPosition()
            main_win.pointPicker.Pick(x, y, 0, main_win.ren1)
            x1, y1, z1 = main_win.pointPicker.GetPickPosition()
            main_win.addSphereActor(x1, y1, z1)
            
        
    def sliceForward(self, obj, e):
        global swc, main_win, mostd_src, show_width, show_height
        cur_line_index = main_win.line_index
        cur_line =  main_win.lines[cur_line_index]
        cur_line_length = len(cur_line)
        cur_slice = main_win.image_slice
        if cur_slice + 1 < cur_line_length:
            next_slice = cur_slice + 1
            main_win.show_image = main_win.getImageFromLoaded(next_slice)
            main_win.image_str = main_win.show_image.tostring()
            main_win.im_importer.CopyImportVoidPointer(main_win.image_str, len(main_win.image_str))
            main_win.im_importer.Modified()
            main_win.im_importer.Update()
            main_win.imageLevelFilter.SetInputConnection(main_win.im_importer.GetOutputPort())
            main_win.imageLevelFilter.Modified()
            main_win.imageLevelFilter.Update()
            main_win.image_actor.SetInput(main_win.imageLevelFilter.GetOutput())
            main_win.image_actor.Modified()
            main_win.image_slice = next_slice
            if (main_win.image_slice < 5) or (main_win.image_slice > len(main_win.lines[main_win.line_index]) - 5):
                main_win.sphere_actor_ren2.SetVisibility(False)
            else:
                main_win.sphere_actor_ren2.SetVisibility(True)            
            if main_win.slice_assembly:
                collectionInteractor1 = vtk.vtkCollectionIterator()
                collectionInteractor1.SetCollection(main_win.slice_assembly)
                collectionInteractor1.InitTraversal()              
                for i in xrange(main_win.slice_assembly.GetNumberOfItems()):
                    collectionInteractor1.GetCurrentObject().GetViewProp().SetVisibility(False)
                    collectionInteractor1.GoToNextItem()
            main_win.slice_assembly = main_win.line_assembly_list[main_win.image_slice]
            if main_win.slice_assembly:
                collectionInteractor1 = vtk.vtkCollectionIterator()
                collectionInteractor1.SetCollection(main_win.slice_assembly)
                collectionInteractor1.InitTraversal()              
                for i in xrange(main_win.slice_assembly.GetNumberOfItems()):
                    collectionInteractor1.GetCurrentObject().GetViewProp().SetVisibility(True)
                    collectionInteractor1.GoToNextItem()
            else:
                main_win.slice_assembly = vtk.vtkAssemblyPath()
                main_win.line_assembly_list[main_win.image_slice]  = main_win.slice_assembly
            main_win.vtk_widget.Render()            
            main_win.renderActorsInSlice()
        else:
            next_slice = cur_slice
        
        
    def sliceBackward(self, obj, e):
        global swc, main_win, mostd_src, show_width, show_height
        cur_slice = main_win.image_slice
        if cur_slice - 1 >= 0:
            next_slice = cur_slice - 1
            main_win.show_image = main_win.getImageFromLoaded(next_slice)
            main_win.image_str = main_win.show_image.tostring()
            main_win.im_importer.CopyImportVoidPointer(main_win.image_str, len(main_win.image_str))
            main_win.im_importer.Modified()
            main_win.im_importer.Update()
            main_win.imageLevelFilter.SetInputConnection(main_win.im_importer.GetOutputPort())
            main_win.imageLevelFilter.Modified()
            main_win.imageLevelFilter.Update()
            main_win.image_actor.SetInput(main_win.imageLevelFilter.GetOutput())
            main_win.image_actor.Modified()
            main_win.image_slice = next_slice
            if (main_win.image_slice < 5) or (main_win.image_slice > len(main_win.lines[main_win.line_index]) - 5):
                main_win.sphere_actor_ren2.SetVisibility(False)
            else:
                main_win.sphere_actor_ren2.SetVisibility(True)
            if main_win.slice_assembly:
                collectionInteractor1 = vtk.vtkCollectionIterator()
                collectionInteractor1.SetCollection(main_win.slice_assembly)
                collectionInteractor1.InitTraversal()              
                for i in xrange(main_win.slice_assembly.GetNumberOfItems()):
                    collectionInteractor1.GetCurrentObject().GetViewProp().SetVisibility(False)
                    collectionInteractor1.GoToNextItem()
            main_win.slice_assembly = main_win.line_assembly_list[main_win.image_slice]    
            if main_win.slice_assembly:
                collectionInteractor1 = vtk.vtkCollectionIterator()
                collectionInteractor1.SetCollection(main_win.slice_assembly)
                collectionInteractor1.InitTraversal()              
                for i in xrange(main_win.slice_assembly.GetNumberOfItems()):
                    collectionInteractor1.GetCurrentObject().GetViewProp().SetVisibility(True)
                    collectionInteractor1.GoToNextItem()
            else:
                main_win.slice_assembly = vtk.vtkAssemblyPath()
                main_win.line_assembly_list[main_win.image_slice]  = main_win.slice_assembly
            main_win.vtk_widget.Render()
            main_win.renderActorsInSlice()
        else:
            next_slice = 0 


class Main_win(gui.QMainWindow):
    fileStatusChanged = qcore.pyqtSignal()
    def __init__(self):
        super(Main_win, self).__init__()
        self.iniMainWin()
    
    def renderActorsInSlice(self):
        pass
    
    def loadImageFromMostd(self, roi):
        r = MD.Roi(roi, self.mostd_src)
        load_image = r.getImages()
        return load_image[0, :, :]    
    
    def iniMainWin(self):
        self.setWindowTitle('test')
        self.setFixedSize(800, 400)
        
        self.iniMenu()
        self.iniCentralWidget()
        self.iniStatusBar()
#         self.loadFiles()
        self.iniVTK()
        self.iniToorBar()
        
    
    def iniToorBar(self):
        self.toolBar = gui.QToolBar(parent=self)
        self.addToolBar(self.toolBar)
        self.toolBarAction_show = gui.QAction(self.toolBar)
        self.toolBarIcon_show = gui.QIcon(r'G:\sulei\workplace\bouttons\resource\show.png')
        self.toolBarAction_show.setIcon(self.toolBarIcon_show)
        self.toolBar.addAction(self.toolBarAction_show)
        self.toolBarAction_invert = gui.QAction(self.toolBar)
        self.toolBarIcon_invert = gui.QIcon(r'G:\sulei\workplace\bouttons\resource\inverse.png')
        self.toolBarAction_invert.setIcon(self.toolBarIcon_invert)
        self.toolBar.addAction(self.toolBarAction_invert)
        self.toolBarAction_choose = gui.QAction(self.toolBar)
        self.toolBarIcon_choose = gui.QIcon(r'G:\sulei\workplace\bouttons\resource\choose.png')
        self.toolBarAction_choose.setIcon(self.toolBarIcon_choose)
        self.toolBar.addAction(self.toolBarAction_choose)        
        self.toolBarAction_delete = gui.QAction(self.toolBar)
        self.toolBarIcon_delete = gui.QIcon(r'G:\sulei\workplace\bouttons\resource\delete.png')
        self.toolBarAction_delete.setIcon(self.toolBarIcon_delete)
        self.toolBar.addAction(self.toolBarAction_delete)
        self.toolBarAction_cancel = gui.QAction(self.toolBar)            
        self.toolBarIcon_cancel = gui.QIcon(r'G:\sulei\workplace\bouttons\resource\cancel.png')
        self.toolBarAction_cancel.setIcon(self.toolBarIcon_cancel)
        self.toolBar.addAction(self.toolBarAction_cancel)
        self.toolBarAction_show.triggered.connect(self.toolBarAction_showFun)
        self.toolBarAction_invert.setDisabled(True)
        self.toolBarAction_invert.setCheckable(True)
        self.toolBarAction_show.setDisabled(True)
        self.toolBarAction_choose.setDisabled(True)
        self.toolBarAction_delete.setDisabled(True)
        self.toolBarAction_cancel.triggered.connect(self.toolBarAction_cancelFun)
#         self.toolBarAction_cancel.toggled.connect(self.toolBarAction_cancelFun)
        self.toolBarAction_cancel.setDisabled(True)
        self.toolBarAction_choose.setCheckable(True)
        self.toolBarAction_choose.toggled.connect(self.toolBarAction_chooseFun2)
        self.toolBarAction_delete.triggered.connect(self.toolBarAction_deleteFun)
        self.toolBarAction_invert.toggled.connect(self.toolBarAction_invertFun)
    
    def toolBarAction_invertFun(self):
        if self.toolBarAction_invert.isChecked():
            if self.show_image is not None:
                inverted_image = cv.bitwise_not(self.show_image)
                inverted_image_str = inverted_image.tostring()
                self.im_importer.CopyImportVoidPointer(inverted_image_str, len(inverted_image_str))
                self.im_importer.Modified()
                self.im_importer.Update()
                self.imageLevelFilter.SetInput(self.im_importer.GetOutput())
                self.imageLevelFilter.SetLevel(65000)
                self.imageLevelFilter.SetWindow(1070)
                self.imageLevelFilter.Modified()
                self.imageLevelFilter.Update()
                self.image_actor.SetInput(self.imageLevelFilter.GetOutput())
                self.image_actor.Modified()
                self.vtk_widget.Render()
        else:
            if self.show_image is not None:
                inverted_image = self.show_image
                inverted_image_str = inverted_image.tostring()
                self.im_importer.CopyImportVoidPointer(inverted_image_str, len(inverted_image_str))
                self.im_importer.Modified()
                self.im_importer.Update()
                self.imageLevelFilter.SetInput(self.im_importer.GetOutput())
                self.imageLevelFilter.SetLevel(400)
                self.imageLevelFilter.SetWindow(800)
                self.imageLevelFilter.Modified()
                self.imageLevelFilter.Update()
                self.image_actor.SetInput(self.imageLevelFilter.GetOutput())
                self.image_actor.Modified()
                self.vtk_widget.Render()
    
    def expandLines(self):
        new_lines = []
        added_slices_num = 5
        for i in xrange(len(self.lines)):
            line_i = self.lines[i]
            new_line_i = []
            for j in xrange(len(line_i)):
                p1, p2, p3, p4, p5, p6, p7 = line_i[j]
                if j == 0:
                    for k in xrange(added_slices_num):
                        z0 = p5 - (added_slices_num - k)
                        new_line_i.append([p1, p2, p3, p4, z0, p6, p7])
                new_line_i.append([p1, p2, p3, p4, p5, p6, p7])
                if j == len(line_i) - 1:
                    p1, p2, p3, p4, p5, p6, p7 = line_i[j]
                    for k in xrange(added_slices_num):
                        z0 = p5 + (k + 1)
                        new_line_i.append([p1, p2, p3, p4, z0, p6, p7])                    
            new_lines.append(new_line_i)
        return new_lines
 
    def toolBarAction_cancelFun(self):
        self.slice_assembly.RemoveItem(self.last_added_sphere_ren1)
        self.slice_assembly.Modified()
        self.ren1_sphere_actors.RemoveItem(self.last_added_sphere_ren1)
        self.ren1_sphere_actors.Modified()
        self.ren1.RemoveActor(self.last_added_sphere_ren1)
        self.ren1.Modified()
        self.ren1.Render()
        self.vtk_widget.Render()
        n = self.newed_spheres.GetNumberOfItems()
        if self.newed_spheres.GetNumberOfItems() != 0:
            tmp_actor = self.newed_spheres.GetItemAsObject(n - 1)
            self.newed_spheres.RemoveItem(tmp_actor)
            self.last_added_sphere_ren1 = tmp_actor
        else:
            self.last_added_sphere_ren1 = None
        if self.newed_spheres.GetNumberOfItems() == 0 and self.last_added_sphere_ren1 == None:
            self.toolBarAction_cancel.setDisabled(True)
        
            
    def saveSwcAction(self):
        self.saveSwcFileDialog = gui.QFileDialog(self)
        file_name = self.saveSwcFileDialog.getOpenFileName(caption='Get Save File', filter='Boutton File (*.bouttons)', directory='.\\')
        file1 = open(file_name, 'w')
        actor_num = self.ren1_sphere_actors.GetNumberOfItems()
        b = [0.0] * 3
        self.ren1_sphere_actors.InitTraversal()
        for i in xrange(actor_num):
            actor_i = self.ren1_sphere_actors.GetNextActor()
            actor_i.maFieldData.GetArray('Locations').GetTupleValue(0, b)
            x, y, z = b
            line_index = actor_i.maFieldData.GetArray('Indices').GetValue(0)
            slice_index = actor_i.maFieldData.GetArray('Indices').GetValue(1)
            is_new = actor_i.maFieldData.GetArray('IsNew').GetValue(0)
            str_line = '%d %d %.6f %.6f %.6f\r\n'%(line_index, slice_index, x, y, z)
            file1.write(str_line)
        file1.close()
        self.statusBar.showMessage("Bouttons Have Been Saved.")
    
    def toolBarAction_deleteFun(self):
        if self.pickedActor:
            self.slice_assembly.RemoveItem(self.pickedActor)
            self.ren1_sphere_actors.RemoveItem(self.pickedActor)
            self.ren1.RemoveActor(self.pickedActor)          
            if self.last_added_sphere_ren1:
                if self.last_added_sphere_ren1 == self.pickedActor:
                    n = self.newed_spheres.GetNumberOfItems()
                    if n != 0:
                        self.last_added_sphere_ren1 = self.newed_spheres.GetItemAsObject(n)
                        self.newed_spheres.RemoveItem(self.last_added_sphere_ren1)
                    else:
                        self.last_added_sphere_ren1 = None
                        self.toolBarAction_cancel.setDisabled(True)
                else:
                        self.newed_spheres.RemoveItem(self.pickedActor)
            self.pickedActor = None            
            self.vtk_widget.Render()
    
    def toolBarAction_chooseFun2(self):
        if not self.toolBarAction_choose.isChecked():
            if self.pickedActor:
                self.pickedActor.GetProperty().SetColor(1.0, 0.0, 1.0)
                self.pickedActor = None
            self.vtk_widget.Render()
            self.toolBarAction_delete.setDisabled(True)
            self.toolBarAction_cancel.setEnabled(True)
        else:
            self.toolBarAction_delete.setEnabled(True)
            self.toolBarAction_cancel.setDisabled(True)
 
    def toolBarAction_showFun (self):
        s = self.lineEditInLeftDock.spinBox.value()
        if s:
            self.line_index = int(s) - 1
            self.statusBar.showMessage('Loading Images...')
            t = Thread(target=self.initImages)
            t.start()
            t.join()
            self.statusBar.showMessage('Images Have Been Loaded.')        
            self.showImages()
        else:
            self.line_index = 0
            self.statusBar.showMessage('Loading Images...')
            t = Thread(target=self.initImages)
            t.start()
            t.join()
            self.statusBar.showMessage('Images Have Been Loaded.')        
            self.showImages()    
    
    def loadActorsFromFile(self):
        global show_height, show_width
        file1 = open(self.bouttons_src)
        for line_i in file1:
            list_i = line_i.strip().split(' ')
            line_index = int(list_i[0])
            slice_index = int(list_i[1])
            x1, y1, z1 = self.lines[line_index][slice_index][2 : 5]
            x0 = int(x1 * 10 / 3 - show_width / 2)
            y0 = int(y1 * 10 / 3 - show_height / 2)
            x = float(list_i[2])
            y = float(list_i[3])
            z = float(list_i[4])
            index_array = vtk.vtkIntArray()
            index_array.SetNumberOfComponents(1)
            index_array.InsertNextValue(line_index)
            index_array.InsertNextValue(slice_index)
            location_array = vtk.vtkFloatArray()
            location_array.SetNumberOfComponents(3)
            location_array.InsertNextTupleValue((x, y, z))
            isNewArray = vtk.vtkIntArray()
            isNewArray.SetNumberOfComponents(1)
            isNewArray.InsertNextValue(0)
            index_array.SetName('Indices')
            location_array.SetName('Locations')
            isNewArray.SetName('IsNew')
            actor1 = MyActor()
            actor1.maFieldData.AddArray(index_array)
            actor1.maFieldData.AddArray(location_array)
            actor1.maFieldData.AddArray(isNewArray)
            actor1.GetProperty().SetColor(255.0, 0, 255.0)
            sphere1 = vtk.vtkSphereSource()
            sphere1.SetCenter(x - x0, y - y0, 0)
            sphere1.SetRadius(self.sphere_radius_ren1)
            mapper1 = vtk.vtkPolyDataMapper()
            mapper1.SetInputConnection(sphere1.GetOutputPort())
            actor1.SetMapper(mapper1)
            self.ren1_sphere_actors.AddItem(actor1)
            matrix1 = vtk.vtkMatrix4x4()
            actor1.SetVisibility(False)
            if self.ren1AssemblyList[line_index] is None:
                self.ren1AssemblyList[line_index] = [None] * len(self.lines[line_index])
            if self.ren1AssemblyList[line_index][slice_index] is None:
                assembly1 = vtk.vtkAssemblyPath()
                self.ren1AssemblyList[line_index][slice_index] = assembly1
            self.ren1AssemblyList[line_index][slice_index].AddNode(actor1, matrix1)
            self.ren1.AddActor(actor1)
        file1.close()
    
    
    def addSphereActor(self, x1, y1, z1):
        x0, y0, z0 = self.roi_list[self.image_slice]
        index_array = vtk.vtkIntArray()
        index_array.SetNumberOfComponents(1)
        index_array.InsertNextValue(self.line_index)
        index_array.InsertNextValue(self.image_slice)
        index_array.SetName('Indices')
        location_array = vtk.vtkDoubleArray()
        location_array.SetName('Locations')
        location_array.SetNumberOfComponents(3)
        location_array.InsertNextTupleValue((x0 + x1, y0 + y1, z0 + z1))
        isNewArray = vtk.vtkIntArray()
        isNewArray.SetName('IsNew')
        isNewArray.SetNumberOfComponents(1)
        isNewArray.InsertNextValue(1)
        new_sphere = vtk.vtkSphereSource()
        new_sphere.SetRadius(self.sphere_radius_ren1)
        new_sphere.SetCenter(x1, y1, 0)
        new_mapper = vtk.vtkPolyDataMapper()
        new_mapper.SetInputConnection(new_sphere.GetOutputPort())
        new_sphere_actor = MyActor()
        matrix1 = vtk.vtkMatrix4x4()
        new_sphere_actor.maFieldData.AddArray(index_array)
        new_sphere_actor.maFieldData.AddArray(location_array)
        new_sphere_actor.maFieldData.AddArray(isNewArray)
        self.bouttons_spheres.append(new_sphere_actor)
        new_sphere_actor.SetMapper(new_mapper)
        new_sphere_actor.GetProperty().SetColor(255.0, 0, 255.0)
        self.ren1_sphere_actors.AddItem(new_sphere_actor)
        self.slice_assembly.AddNode(new_sphere_actor, matrix1)
        if self.last_added_sphere_ren1 is None:
            self.toolBarAction_cancel.setEnabled(True)
        else:
            self.newed_spheres.AddItem(self.last_added_sphere_ren1)
        self.last_added_sphere_ren1 = new_sphere_actor
        self.ren1.AddActor(new_sphere_actor)
        self.slice_assembly.Modified()
        self.ren1.GetRenderWindow().Render()  
    
    
    def iniVTK(self):
        self.last_added_sphere_ren1 = None
        self.newed_spheres = vtk.vtkCollection()
        self.sphere_radius_ren1 = 2.0
        self.bouttons_spheres = []
        self.slice_assembly = None
        self.image_roi = None
        self.im_importer = vtk.vtkImageImport()       
        self.sphere = vtk.vtkSphereSource()
        self.sphere.SetRadius(2.0)
        self.sphere_mapper = vtk.vtkPolyDataMapper()
        self.sphere_mapper.SetInputConnection(self.sphere.GetOutputPort())
        self.sphere_actor_ren2 = vtk.vtkActor()
        self.sphere.SetCenter(show_height / 2, show_width / 2, 0)
        self.sphere_actor_ren2.SetMapper(self.sphere_mapper)
        self.sphere_actor_ren2.GetProperty().SetColor(255.0, 0, 0)
        self.vtk_widget.GetRenderWindow().SetSize(800, 400)
        self.image_actor = vtk.vtkImageActor()
        self.ren1 = vtk.vtkRenderer()
        self.ren2 = vtk.vtkRenderer()
        self.interactorStyle = BouttonInteractorStyle()
        self.vtk_widget.SetInteractorStyle(self.interactorStyle)
        self.vtk_widget.GetRenderWindow().AddRenderer(self.ren1)
        self.vtk_widget.GetRenderWindow().AddRenderer(self.ren2)
        self.ren1.SetViewport(0.0, 0.0, 0.5, 1.0)
        self.ren2.SetViewport(0.5, 0.0, 1.0, 1.0)
        self.ren2.AddActor(self.sphere_actor_ren2)
        self.imageLevelFilter = vtk.vtkImageMapToWindowLevelColors()
        self.imageLevelFilter.SetLevel(400)
        self.imageLevelFilter.SetWindow(800)
        self.im_importer.SetNumberOfScalarComponents(1)
        self.im_importer.SetDataScalarTypeToUnsignedShort()
        self.im_importer.SetDataExtent(0, show_width - 1, 0, show_height - 1, 0, 0)
        self.im_importer.SetWholeExtent(0, show_width - 1, 0, show_height - 1, 0, 0)
        self.imageLevelFilter.SetInputConnection(self.im_importer.GetOutputPort())
        self.image_actor.SetInput(self.imageLevelFilter.GetOutput())
        self.ren1_sphere_actors = vtk.vtkActorCollection()
        self.pointPicker = vtk.vtkPointPicker()
        self.actorPicker = vtk.vtkPropPicker()
        self.pickedActor = None
        self.ren1.AddActor(self.image_actor)
        self.ren2.AddActor(self.image_actor)

    def showImages(self):
        global show_width, show_height
        if (self.image_slice < 5) or (self.image_slice > len(main_win.lines[main_win.line_index]) - 5):
            self.sphere_actor_ren2.SetVisibility(False)
        else:
            self.sphere_actor_ren2.SetVisibility(True)
        self.show_image = self.getImageFromLoaded(self.image_slice)
        self.image_str = self.show_image.tostring()
        self.im_importer.CopyImportVoidPointer(self.image_str, len(self.image_str))
        self.im_importer.Update()
        self.vtk_widget.Initialize()
        self.vtk_widget.Start()
        self.toolBarAction_choose.setEnabled(True)
        self.toolBarAction_delete.setEnabled(False)
        self.toolBarAction_invert.setEnabled(True)

    def loadFiles(self):
        if self.swc_src:
            swc = stree.SwcTree(self.swc_src)
            if swc:
                self.lines = swc.getLines()
                self.lines = self.expandLines()
                self.ren1AssemblyList = [None] * len(self.lines)
                self.load_swc_action.setEnabled(False)  
        if self.mostd_src:
            if re.match('.+\.[Mm][Oo][Ss][Tt][Dd]$', self.mostd_src):
                self.load_mostd_action.setEnabled(False)
        if self.swc_src and self.mostd_src and not self.bouttons_src:
            self.toolBarAction_show.setEnabled(True)
            self.load_boutton_action.setEnabled(True)
            self.statusBar.showMessage('swc: 1, most: 1, ready.')
            self.image_slice = 0
            self.line_index = 0
            self.iniLeftDockWidget()
        if self.bouttons_src:
            if re.match('.+\.[Bb][Oo][Uu][Tt][Tt][Oo][Nn]', self.bouttons_src):
                self.load_boutton_action.setEnabled(False)
                self.loadActorsFromFile()
            
    def initImages(self):
        global show_height, show_width, show_thickness
        if self.slice_assembly:
            collectioniteractor1 = vtk.vtkCollectionIterator()
            collectioniteractor1.SetCollection(self.slice_assembly)
            collectioniteractor1.InitTraversal()
            for i in xrange(self.slice_assembly.GetNumberOfItems()):
                collectioniteractor1.GetCurrentObject().GetViewProp().SetVisibility(False)
                collectioniteractor1.GoToNextItem()
        if self.ren1AssemblyList[self.line_index]:
            self.line_assembly_list = self.ren1AssemblyList[self.line_index]
        else:
            self.line_assembly_list = [None] * len(self.lines[self.line_index])
            self.ren1AssemblyList[self.line_index] = self.line_assembly_list
        t0 = time.clock()
        self.images = [None] * len(self.lines[self.line_index])
        self.roi_list = []
        self.image_slice = 0
        self.countRoiInLine()
        if self.line_assembly_list[self.image_slice]:
            self.slice_assembly = self.line_assembly_list[self.image_slice]
            collectioniteractor1 = vtk.vtkCollectionIterator()
            collectioniteractor1.SetCollection(self.slice_assembly)
            collectioniteractor1.InitTraversal()
            for i in xrange(self.slice_assembly.GetNumberOfItems()):
                collectioniteractor1.GetCurrentObject().GetViewProp().SetVisibility(True)
                collectioniteractor1.GoToNextItem()
        else:
            self.slice_assembly = vtk.vtkAssemblyPath()
            self.line_assembly_list[self.image_slice] = self.slice_assembly
        self.load_mx_num = 100
        if self.load_mx_num > len(self.lines[self.line_index]):
            real_load_num = len(self.lines[self.line_index])
        else:
            real_load_num = self.load_mx_num
#         print real_load_num, len(self.lines[self.line_index])
        for i in xrange(real_load_num):
            x0, y0, z0 = self.lines[self.line_index][i][2 : 5]
            x_s = int((x0 * 10 / 3 - show_width / 2))
            y_s = int((y0 * 10 / 3 - show_height / 2))
            z_s = int(z0)
            tmp_image = np.zeros((show_height, show_width), dtype=np.uint16)
            for j in xrange((- show_thickness), show_thickness + 1):
                z_i = z_s + j
                if z_i < 0:
                    z_i = 0
                image_roi = (x_s, y_s, z_i, show_width, show_height, 1)            
                image_j = self.loadImageFromMostd(image_roi)
                tmp_image = np.maximum(tmp_image, image_j);
            self.images[i] = tmp_image
        print time.clock() - t0
    
    
    def countRoiInLine(self):
        line1 = self.lines[self.line_index]
        for i in xrange(len(line1)):
            x0, y0, z0 = line1[i][2 : 5]
            x_s = int((x0 * 10 / 3 - show_width / 2))
            y_s = int((y0 * 10 / 3 - show_height / 2))
            z_s = int(z0)
            self.roi_list.append((x_s, y_s, z_s))
    
    def reloadImages(self, s):
        global show_height, show_width, show_thickness
        t0 = time.clock()
        load_oritation = s - self.image_slice
        if load_oritation > 0:
            load_beg = s
            del_beg = s - self.load_mx_num
            del_end = s - self.load_mx_num / 2 - 1
            load_end = s + self.load_mx_num / 2 - 1
        elif load_oritation < 0:
            del_beg = s + self.load_mx_num / 2 + 1
            del_end = s + self.load_mx_num
            load_beg = s - self.load_mx_num /2 + 1
            load_end = s 

        if load_end >= len(self.lines[self.line_index]):
            load_end = len(self.lines[self.line_index]) - 1 
        if load_beg < 0:
            load_beg = 0        
        if del_end >= len(self.lines[self.line_index]):
            del_end = len(self.lines[self.line_index]) - 1        
        if del_beg < 0:
            del_beg = 0
        for i in xrange(del_beg, del_end + 1):
            self.images[i] = None
        for i in xrange(load_beg, load_end + 1):
            x0, y0, z0 = self.lines[self.line_index][i][2 : 5]
            x_s = int((x0 * 10 / 3 - show_width / 2))
            y_s = int((y0 * 10 / 3 - show_height / 2))
            z_s = int(z0)         
            tmp_image = np.zeros((show_height, show_width), dtype=np.uint16)
            for j in xrange((- show_thickness), show_thickness + 1):
                z_i = z_s + j
                if z_i < 0:
                    z_i = 0
                image_roi = (x_s, y_s, z_i, show_width, show_height, 1)            
                image_j = self.loadImageFromMostd(image_roi)
                tmp_image = np.maximum(tmp_image, image_j);
            self.images[i] = tmp_image
        print time.clock() - t0       
    
    def getImageFromLoaded(self, s):
        if self.images[s] is not None:
            if self.toolBarAction_invert.isChecked():
                returned_image = cv.bitwise_not(self.images[s])
            else:
                returned_image = self.images[s]
        else:
            self.statusBar.showMessage('Reload Images......')
            t = Thread(target=self.reloadImages, args=(s, ))
            t.start()
            t.join()
            self.reloadImages(s)
            self.statusBar.showMessage('Reload Completed.')
            if self.toolBarAction_invert.isChecked():
                returned_image = cv.bitwise_not(self.images[s])
            else:
                returned_image = self.images[s]
        return returned_image
        

    def iniStatusBar(self):
        self.statusBar = gui.QStatusBar(self)
        self.setStatusBar(self.statusBar)
        self.statusBar.showMessage('swc: 0, mostd: 0, not already.')
    
    def iniCentralWidget(self):
        self.centralWidget = gui.QWidget()
        self.centralLayout = gui.QHBoxLayout()
        self.vtk_widget = QVTKRenderWindowInteractor(self.centralWidget)
        self.setCentralWidget(self.centralWidget)
        self.centralWidget.setLayout(self.centralLayout)
        self.centralLayout.addWidget(self.vtk_widget)  
    
    def iniMenu(self):
        self.bouttons_src = None
        self.mostd_src = None
        self.swc_src = None
        self.fileStatusChanged.connect(self.loadFiles)        
        self.menuBar = gui.QMenuBar(self)
        self.menu_load = gui.QMenu('Load File', self)
        self.menu_save = gui.QMenu('Save File', self)
        self.load_swc_action = gui.QAction('Load Swc', self.menu_load)
        self.load_mostd_action = gui.QAction('Load Mostd', self.menu_load)
        self.load_boutton_action = gui.QAction('Load Bouttons', self.menu_load)
        self.menu_load.addAction(self.load_mostd_action)
        self.menu_load.addAction(self.load_swc_action)
        self.menu_load.addAction(self.load_boutton_action)
        self.save_swc_action = gui.QAction('Save Swc', self.menu_save)
        self.menu_save.addAction(self.save_swc_action)
        self.menuBar.addMenu(self.menu_load)
        self.menuBar.addMenu(self.menu_save)
        self.setMenuBar(self.menuBar)
        self.load_boutton_action.setEnabled(False)
        self.load_mostd_action.triggered.connect(self.loadMostd)
        self.load_swc_action.triggered.connect(self.loadSwc)
        self.save_swc_action.triggered.connect(self.saveSwcAction)
        self.load_boutton_action.triggered.connect(self.loadBouttons)
        
    def loadMostd(self):
        self.loadMostdDialog = gui.QFileDialog(parent=self)
        self.mostd_src = self.loadMostdDialog.getOpenFileName(caption='Load Mostd', filter='Mostd Files (*.mostd)', directory='.')
        self.fileStatusChanged.emit()
    
    def loadSwc(self):
        self.loadSwcDialog = gui.QFileDialog(parent=self)
        self.swc_src = self.loadSwcDialog.getOpenFileName(caption='Load Swc', filter='Swc Files (*.swc)', directory='.')
        self.fileStatusChanged.emit()
    
    def loadBouttons(self):
        self.loadBouttonsDialog = gui.QFileDialog()
        self.bouttons_src = self.loadBouttonsDialog.getOpenFileName(caption='Load Bouttons', filter='Bouttons File (*.bouttons)', directory='.')
        self.fileStatusChanged.emit()
    
    def iniLeftDockWidget(self):
        self.leftDockWidget1 = gui.QDockWidget(parent=self)
        self.leftDockWidget1.setFixedSize(100, 60)
        self.leftDockWidget1.setAllowedAreas(qcore.Qt.LeftDockWidgetArea)
        self.addDockWidget(qcore.Qt.LeftDockWidgetArea, self.leftDockWidget1)
        self.lineEditInLeftDock = ChoooseNLineWidget(len(self.lines))
        self.leftDockWidget1.setWidget(self.lineEditInLeftDock)
        self.leftDockWidget2 = gui.QDockWidget(parent=self)
        self.leftDockWidget2.setFixedSize(100, 60)
        self.leftDockWidget2.setAllowedAreas(qcore.Qt.LeftDockWidgetArea)
        self.addDockWidget(qcore.Qt.LeftDockWidgetArea, self.leftDockWidget2)
        self.labelInLeftDock = gui.QLabel(parent=self.leftDockWidget2)
        self.leftDockWidget2.setWidget(self.labelInLeftDock)
        self.labelInLeftDock.setAlignment(qcore.Qt.AlignHCenter | qcore.Qt.AlignTop)
        self.labelInLeftDock.setText('swc: 0, mostd: 0,\n not already.')
        


if __name__ == '__main__':
    global swc, lines, mostd_src, load_images, main_win, show_width, show_height
    show_width = 100
    show_height = 100
    show_thickness = 1
    app = gui.QApplication(sys.argv)
    main_win = Main_win()
    main_win.show()
    sys.exit(app.exec_())
    
    
    
    
    
    
#         image2 = np.uint8(image3 / 16)
#         image2 = cv.cvtColor(image2, cv.cv.CV_GRAY2RGB)
#         image2[y0 - y_s + 1, x0 - x_s + 1, 0] = 255
#         image2[y0 - y_s + 1, x0 - x_s + 1, 1] = 0
#         image2[y0 - y_s + 1, x0 - x_s + 1, 2] = 0
    