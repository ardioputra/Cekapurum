#image node (apt install node ver 14)
FROM node:14 

#making directory work container cekapurum
WORKDIR ./cekapurum

#copying package.json to inside directory
COPY package*.json ./

#install npm
RUN npm install

#copying all files in local directory to work directory
COPY . .

#port expose 80
EXPOSE 80

#for running syntax
CMD node scripts.js