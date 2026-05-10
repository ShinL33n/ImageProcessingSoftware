# Image processing software
System software design C++ project

<table border="1" cellpadding="4" cellspacing="0">
	<tbody>
		<tr>
			<td>
				<p align="CENTER"><font face="Arial"><b>Part of the project being evaluated</b></font></p>
			</td>
			<td>
				<p align="CENTER"><font face="Arial"><b>Tools</b></font></p>
			</td>
			<td>
				<p align="CENTER"><font face="Arial"><b>% of points</b></font></p>
			</td>
		</tr>
		<tr>
			<td><font face="Arial"><b>Description of the requirements using UML</b> </font>
				<ul>
					<li><font face="Arial">identify the client, end users and other parties interested in the results of the project (stakeholders); </font></li>
					<li><font face="Arial">collect and analyze the details of the functional and non-functional requirements for particular tasks; </font></li>
					<li><font face="Arial">determine the usage scenarios and create a functional specification, suitable for reading ; <!-- LI--> </font></li>
					<li><font face="Arial">optionally incorporate a UML usage scenarios to the documentation; <!-- LI--> </font></li>
					<li><font face="Arial">create a UML model the key elements of the proposed solutions; <!-- LI--> </font></li>
					<li><font face="Arial">examine the possibility of using additional libraries and tools for the task; <!-- LI--> </font></li>
					<li><font face="Arial">develop a brief technical specification summarizing this information together with the work schedule; <!-- LI--> </font></li>
					<li><font face="Arial">submit the specification to the teacher. <!-- LI--> </font></li>
				</ul>
				<font face="Arial"> </font></td>
			<td><font face="Arial">Microsoft Visio</font></td>
			<td>
				<p align="CENTER"><font face="Arial">10</font></p>
			</td>
		</tr>
		<tr>
			<td><font face="Arial"><b>Writing simple image processing software </b><br>
				Assumptions: </font>
				<ul>
					<li><font face="Arial">the software should be run from the command line; </font></li>
					<li><font face="Arial">the paths of the source and destination files should be read from * .ini file(for ini file analysis, any free library can be used, for example. iniParser); </font></li>
					<li><font face="Arial">the software should read all image files from the source path; </font></li>
					<li><font face="Arial">the software should convert the&nbsp;images (multi-threaded) - <strong>outline detection</strong>; </font></li>
					<li><font face="Arial">the processed images should be saved in the target folder; </font></li>
					<li><font face="Arial">two images with the matrix of all image thumbnails (one for input files, another for the processed images) should be saved for quick evaluation of the results. </font></li>
				</ul>
				<font face="Arial"> It is suggested that you first familiarize yourself with the various elements of the project: </font>
				<ul>
					<li><font face="Arial">INI file analysis; </font></li>
					<li><font face="Arial">how to read, save and view images in OpenCV; </font></li>
					<li><font face="Arial">the rules for operations on matrices / images in OpenCV; </font></li>
					<li><font face="Arial">select and test the selected image processing method. </font></li>
				</ul>
				<font face="Arial"> </font></td>
			<td><font face="Arial">Visual Studio 2013 i C/C++ with OpenCV library</font></td>
			<td>
				<p align="CENTER"><font face="Arial">20<sup>*</sup></font></p>
			</td>
		</tr>
		<tr>
			<td><font face="Arial"><b>The use of collaboration tools </b> </font>
				<ul>
					<li><font face="Arial">gain the access to the repository version control system (external hosting GitHub, Bitbucket); </font></li>
					<li><font face="Arial">select a person responsible for maintaining order in the repository (maintainer); </font></li>
					<li><font face="Arial">plan your repository structure, depending on your IDE, programming language, additional artifacts (UI graphics, specifications, etc.). </font></li>
				</ul>
				<font face="Arial"> </font></td>
			<td><font face="Arial">GIT + GitHub</font></td>
			<td>
				<p align="CENTER"><font face="Arial">10</font></p>
			</td>
		</tr>
		<tr>
			<td><font face="Arial"><b>Use of the bug tracking system <!-- B--> </b></font>
				<ul>
					<li><font face="Arial"><b>access to the repository of Bug Tracking System (external hosting GitHub, Bitbucket); </b></font></li>
					<li><font face="Arial"><b>select a person responsible for maintaining order in the repository (maintainer). </b></font></li>
					<li><font face="Arial"><b>report the errors detected during testing cycles to the bug tracking system; </b></font></li>
					<li><font face="Arial"><b>optionally, use a method of test-driven development to ensure quality; </b></font></li>
					<li><font face="Arial"><b>demonstrate the use of block testing to validate the key elements of the software. </b></font></li>
				</ul>
				<font face="Arial"><b> </b></font></td>
			<td><font face="Arial">Bugzilla</font></td>
			<td>
				<p align="CENTER"><font face="Arial">10</font></p>
			</td>
		</tr>
		<tr>
			<td><font face="Arial"><b>The use of the threads/processes</b> </font></td>
			<td><font face="Arial">Windows</font></td>
			<td>
				<p align="CENTER"><font face="Arial">10</font></p>
			</td>
		</tr>
		<tr>
			<td><font face="Arial"><b>The use of IPC</b></font></td>
			<td><font face="Arial">Windows</font></td>
			<td>
				<p align="CENTER"><font face="Arial">10</font></p>
			</td>
		</tr>
		<tr>
			<td><font face="Arial"><b>Writing the project documentation <!-- B--> </b></font>
				<ul>
					<li><font face="Arial"><b>implement the appropriate amount of work during your work to document the API (comments compatible with Doxygen) use comments in the code, explaining the particularly confusing algorithms, mechanisms, relationships; </b></font></li>
					<li><font face="Arial"><b>generate HTML documentation from Doxygen comments on a regular basis, not after the completion of the project; <!-- LI--> </b></font></li>
					<li><font face="Arial"><b>provide the documentation to your teacher. <!-- LI--> </b></font>
						<ul></ul>
					</li>
				</ul>
			</td>
			<td><font face="Arial">Doxygen</font></td>
			<td>
				<p align="CENTER"><font face="Arial">10</font></p>
			</td>
		</tr>
		<tr>
			<td><font face="Arial"><b>Profiling of the project (detection of hotspots) </b> </font>
				<ul>
					<li><font face="Arial">use the profiler to detect the hotspots in your software, try to optimize the code.</font></li>
				</ul>
				<font face="Arial"> </font></td>
			<td><font face="Arial">Visual Studio Profiler</font></td>
			<td>
				<p align="CENTER"><font face="Arial">10</font></p>
			</td>
		</tr>
		<tr>
			<td><font face="Arial"><b>Detecting memory leaks</b> </font>
				<ul>
					<li><font face="Arial">for example, use macro <code>_ASSERTE( _CrtCheckMemory( ) );</code> in DEBUG mode and check the data integrity in your code.</font></li>
				</ul>
			</td>
			<td><font face="Arial">Visual Studio + CrtCheckMemory</font></td>
			<td>
				<p align="CENTER"><font face="Arial">10</font></p>
			</td>
		</tr>
	</tbody>
</table>
