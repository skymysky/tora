//***************************************************************************
/*
 * TOra - An Oracle Toolkit for DBA's and developers
 * Copyright (C) 2000-2001,2001 GlobeCom AB
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;  only version 2 of
 * the License is valid for this program.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 *      As a special exception, you have permission to link this program
 *      with the Oracle Client libraries and distribute executables, as long
 *      as you follow the requirements of the GNU GPL in regard to all of the
 *      software in the executable aside from Oracle client libraries. You
 *      are also allowed to link this program with the Qt Non Commercial for
 *      Windows.
 *
 *      Specifically you are not permitted to link this program with the
 *      Qt/UNIX or Qt/Windows products of TrollTech. And you are not
 *      permitted to distribute binaries compiled against these libraries
 *      without written consent from GlobeCom AB. Observe that this does not
 *      disallow linking to the Qt Free Edition.
 *
 * All trademarks belong to their respective owners.
 *
 ****************************************************************************/

#include "toresultreferences.h"
#include "tomain.h"
#include "totool.h"
#include "toconf.h"
#include "tosql.h"
#include "toconnection.h"

toResultReferences::toResultReferences(QWidget *parent,const char *name)
  : toResultView(false,false,parent,name)
{
  setReadAll(true);
  addColumn("Owner");
  addColumn("Object");
  addColumn("Constraint");
  addColumn("Condition");
  addColumn("Enabled");
  addColumn("Delete Rule");
  setSQLName("toResultReferences");
}

static toSQL SQLConsColumns("toResultReferences:ForeignColumns",
			    "SELECT Column_Name FROM All_Cons_Columns\n"
			    " WHERE Owner = :f1<char[101]> AND Constraint_Name = :f2<char[101]>\n"
			    " ORDER BY Position",
			    "Get columns of foreign constraint, must return same number of cols");

QString toResultReferences::constraintCols(const QString &conOwner,const QString &conName)
{
  toQuery query(connection(),SQLConsColumns,conOwner,conName);

  QString ret;
  while(!query.eof()) {
    QString value=query.readValue();
    if (!ret.isEmpty())
      ret.append(",");
    ret.append(value);
  }
  return ret;
}

static toSQL SQLConstraints("toResultReferences:References",
			    "SELECT Owner,\n"
			    "       Table_Name,\n"
			    "       Constraint_Name,\n"
			    "       R_Owner,\n"
			    "       R_Constraint_Name,\n"
			    "       Status,\n"
			    "       Delete_Rule\n"
			    "  FROM all_constraints a\n"
			    " WHERE constraint_type = 'R'\n"
			    "   AND (r_owner,r_constraint_name) IN (SELECT b.owner,b.constraint_name\n"
			    "                                         FROM all_constraints b\n"
			    "                                        WHERE b.OWNER = :owner<char[101]>\n"
			    "                                          AND b.TABLE_NAME = :tab<char[101]>)\n"
			    " ORDER BY Constraint_Name",
			    "List the references from foreign constraints to specified table, must return same columns");
static toSQL SQLDependencies("toResultReferences:Dependencies",
			     "SELECT owner,name,type||' '||dependency_type\n"
			     "  FROM all_dependencies\n"
			     " WHERE referenced_owner = :owner<char[101]>\n"
			     "   AND referenced_name = :tab<char[101]>\n"
			     " ORDER BY owner,type,name",
			     "List the dependencies from other objects to this object, must return same number of columns",
			     "8.0");
static toSQL SQLDependencies7("toResultReferences:Dependencies",
			      "SELECT owner,name,type\n"
			      "  FROM all_dependencies\n"
			      " WHERE referenced_owner = :owner<char[101]>\n"
			      "   AND referenced_name = :tab<char[101]>\n"
			      " ORDER BY owner,type,name",
			      QString::null,
			      "7.3");

void toResultReferences::query(const QString &sql,const toQList &param)
{
  if (!handled())
    return;

  QString Owner;
  QString TableName;
  toQList::iterator cp=((toQList &)param).begin();
  if (cp!=((toQList &)param).end())
    Owner=*cp;
  cp++;
  if (cp!=((toQList &)param).end())
    TableName=(*cp);

  Query=NULL;
  RowNumber=0;

  clear();

  try {
    toQuery query(connection(),SQLConstraints,Owner,TableName);

    QListViewItem *item=NULL;
    while(!query.eof()) {
      item=new QListViewItem(this,item,NULL);

      QString consOwner(query.readValue());
      item->setText(1,query.readValue());
      QString consName(query.readValue());
      QString colNames(constraintCols(Owner,consName));
      item->setText(0,consOwner);
      item->setText(2,consName);
      QString rConsOwner(query.readValue());
      QString rConsName(query.readValue());
      item->setText(4,query.readValue());
      QString Condition;

      Condition="foreign key (";
      Condition.append(colNames);
      Condition.append(") references ");
      Condition.append(rConsOwner);
      Condition.append(".");
      QString cols(constraintCols(rConsOwner,rConsName));
      
      Condition.append(TableName);
      Condition.append("(");
      Condition.append(cols);
      Condition.append(")");

      item->setText(3,Condition);
      item->setText(5,query.readValue());
    }
    
    toQuery deps(connection(),SQLDependencies,Owner,TableName);
    while(!deps.eof()) {
      item=new QListViewItem(this,item,NULL);
      item->setText(0,deps.readValue());
      item->setText(1,deps.readValue());
      item->setText(3,deps.readValue());
      item->setText(4,"DEPENDENCY");
    }
  } TOCATCH
  updateContents();
}
