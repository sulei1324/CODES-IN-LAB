#include "stdafx.h"
#include "SwcReader.h"

SwcReader::~SwcReader()
{

}

void SwcReader::SetInputName(const string &arg)
{
    swcName = arg;
    isInit = true;
}

bool SwcReader::Update()
{
    if(isInit){
        string tmpLine;
        char tmpChars[512];
        v7iSwc vec7iSwc;
        vLine vecLine;
        vec5i tmpPoint;
        std::ifstream swcFile(swcName.c_str(), std::ios::in);
        //swcFile.open();
        while(swcFile.getline(tmpChars, 512)){
            tmpLine = tmpChars;
            //cout<<tmpLine<<endl;
            std::stringstream tmpLineStream(tmpLine);
            vector<int> tmpInts;
            double tmpDou;
            while(tmpLineStream>>tmpDou){
                tmpInts.push_back(static_cast<int>(tmpDou));
            }
            if(tmpInts.size() != 7){
                cout<<"Line Error!"<<endl;
                return false;
            }else{
                vec7i tmpVec7i;
                vector<int>::iterator iter = tmpInts.begin();
                int i = 0;
                for(; iter != tmpInts.end(); ++iter){
                    tmpVec7i[i] = *iter;
                    ++i;
                }
                vec7iSwc.push_back(tmpVec7i);
                if(tmpVec7i[0] != tmpVec7i[6] + 1){
                    //if(tmpVec7i[6] != -1){
                    //    lines.push_back(vecLine);
                    //}
                    if(vecLine.size() != 0){
                        lines.push_back(vecLine);
                        vecLine.clear();
                        if(tmpVec7i[6] != -1){
                            vec7i preVecSwcLine = vec7iSwc[tmpVec7i[6] - 1];
                            tmpPoint<<preVecSwcLine[0], preVecSwcLine[2], preVecSwcLine[3], preVecSwcLine[4], preVecSwcLine[6];
                            vecLine.push_back(tmpPoint);
                        }
                    }
                }
                tmpPoint<<tmpVec7i[0], tmpVec7i[2], tmpVec7i[3], tmpVec7i[4],  tmpVec7i[6];
                vecLine.push_back(tmpPoint); 
            }
        }
        lines.push_back(vecLine);
        isUpdated = true;
        return true;
    }else{
        return false;  
    }
    
}

vLines& SwcReader::GetOutput()
{
    return lines;
}

SwcReader::SwcReader()
{
    isInit = false;
    isUpdated = false;
}

void SwcReader::PrintLines()
{
    if(lines.size() != 0){
        vector<vLine>::iterator iter = lines.begin();
        for(; iter != lines.end(); ++iter){
            vLine tmpLine = *iter;
            if(tmpLine.size() != 0){
                vector<vec5i>::iterator iterInner = tmpLine.begin();
                cout<<"---------------------------------"<<endl;
                while(iterInner != tmpLine.end()){
                    cout<<*iterInner<<endl;
                    ++iterInner;
                }
                cout<<"*********************************"<<endl;
            }
        }
    }
}

bool SwcReader::BuildActors(vtk_sp(vtkRenderer, arg), double ratio)
{
    if(isUpdated && isInit && ratio != 0){
        ren = arg;
        vLines::size_type lineNum = lines.size();
        vLines::size_type iterI = 0;
        lineActors = vtk_new(vtkActorCollection);
        vertActors = vtk_new(vtkActorCollection);
        for(; iterI < lineNum; ++iterI){
            vLine curLine = lines.at(iterI);
            vLine::size_type curLinePointNum = curLine.size();
            vLine::size_type iterPoint = 0;
            vtk_spnew(vtkPoints, linePoints);
            vtk_spnew(vtkPoints, vertPoints);
            vtk_spnew(vtkCellArray, lineCells);
            vtk_spnew(vtkCellArray, vertCells);
            vtk_spnew(vtkPolyData, linePoly);
            vtk_spnew(vtkPolyData, vertPoly);
            vtk_spnew(vtkPolyDataMapper, lineMapper);
            vtk_spnew(vtkPolyDataMapper, vertMapper);
            vtk_spnew(vtkActor, lineActor);
            vtk_spnew(vtkActor, vertActor);
            lineCells->InsertNextCell(curLinePointNum);
            vertCells->InsertNextCell(2);
            for(; iterPoint < curLinePointNum; ++iterPoint){
                vPoint curPoint = curLine.at(iterPoint);
                curPoint(1)  = static_cast<int>(curPoint(1) / ratio);
                curPoint(2) = static_cast<int>(curPoint(2) / ratio);
                linePoints->InsertNextPoint(curPoint(1), curPoint(2), curPoint(3));
                lineCells->InsertCellPoint(iterPoint);
                if(iterPoint == 0){
                    vertPoints->InsertNextPoint(curPoint(1), curPoint(2), curPoint(3));
                    vertCells->InsertCellPoint(0);
                }else if(iterPoint == curLinePointNum - 1){
                    vertPoints->InsertNextPoint(curPoint(1), curPoint(2), curPoint(3));
                    vertCells->InsertCellPoint(1);
                }
            }
            linePoly->SetPoints(linePoints);
            linePoly->SetLines(lineCells);
            vertPoly->SetPoints(vertPoints);
            vertPoly->SetVerts(vertCells);
            lineMapper->SetInput(linePoly);
            vertMapper->SetInput(vertPoly);
            lineActor->SetMapper(lineMapper);
            vertActor->SetMapper(vertMapper);
            lineActors->AddItem(lineActor);
            lineActor->GetProperty()->SetLineWidth(2.0);
            lineActor->GetProperty()->SetColor(vtkMath::Random(0.0, 1.0), vtkMath::Random(0.0, 1.0), vtkMath::Random(0.0, 1.0));
            vertActor->GetProperty()->SetPointSize(3.0);
            vertActor->GetProperty()->SetColor(vtkMath::Random(0.0, 1.0), vtkMath::Random(0.0, 1.0), vtkMath::Random(0.0, 1.0));
            
            vertActors->AddItem(vertActor);
            ren->AddActor(lineActor);
            ren->AddActor(vertActor);
        }
        return true;  
    }else{
        return false;
    }

}
